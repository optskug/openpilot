#include <unistd.h>

#include <cstdlib>
#include <fstream>
#include <string>

#include <QDebug>
#include <QDir>
#include <QTimer>
#include <QVBoxLayout>
#include <QProcessEnvironment>

#include "common/util.h"
#include "selfdrive/ui/installer/installer.h"
#include "selfdrive/ui/qt/util.h"
#include "selfdrive/ui/qt/qt_window.h"

#define RELEASE_USER "commaai"
#define RELEASE_BRANCH "devel"
#define NIGHTLY_USER "commaai"
#define NIGHTLY_BRANCH "nightly-dev"
#define TSKM_USER "optskug"
#define TSKM_BRANCH "tskm-0.9.8"

#define PATH_RELEASE_GIT_CLONE "/data/tsk-release"  // Must match tsk/reboot_menu/actions.py
#define PATH_NIGHTLY_GIT_CLONE "/data/tsk-nightly"  // Must match tsk/reboot_menu/actions.py
#define PATH_TSKM_GIT_CLONE "/data/tsk-manager"
#define PATH_OP_INSTALL "/data/openpilot"

extern const uint8_t str_continue[] asm("_binary_selfdrive_ui_installer_continue_openpilot_sh_start");
extern const uint8_t str_continue_end[] asm("_binary_selfdrive_ui_installer_continue_openpilot_sh_end");

void run(const char* cmd) {
  int err = std::system(cmd);
  qDebug() << "Command: " << cmd << ", Exit code: " << err;
  assert(err == 0);
}

Installer::Installer(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setContentsMargins(150, 290, 150, 150);
  layout->setSpacing(0);

  QLabel *title = new QLabel(tr("Installing..."));
  title->setStyleSheet("font-size: 90px; font-weight: 600;");
  layout->addWidget(title, 0, Qt::AlignTop);

  layout->addSpacing(170);

  bar = new QProgressBar();
  bar->setRange(0, 100);
  bar->setTextVisible(false);
  bar->setFixedHeight(72);
  layout->addWidget(bar, 0, Qt::AlignTop);

  layout->addSpacing(30);

  val = new QLabel("0%");
  val->setStyleSheet("font-size: 70px; font-weight: 300;");
  layout->addWidget(val, 0, Qt::AlignTop);

  layout->addStretch();

  QObject::connect(&procGitCloneRelease, &QProcess::readyReadStandardError, this, &Installer::readProgress);
  QObject::connect(&procGitCloneNightly, &QProcess::readyReadStandardError, this, &Installer::readProgress);
  QObject::connect(&procGitCloneTSKM, &QProcess::readyReadStandardError, this, &Installer::readProgress);

  QObject::connect(&procGitCloneRelease, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Installer::cloneReleaseFinishedHandler);
  QObject::connect(&procGitCloneNightly, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Installer::cloneNightlyFinishedHandler);
  QObject::connect(&procGitCloneTSKM, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Installer::cloneTSKMFinishedHandler);

  QTimer::singleShot(100, this, &Installer::doInstall);

  setStyleSheet(R"(
    * {
      font-family: Inter;
      color: white;
      background-color: black;
    }
    QProgressBar {
      border: none;
      background-color: #292929;
    }
    QProgressBar::chunk {
      background-color: #364DEF;
    }
  )");
}

void Installer::updateProgress(int percent) {
  bar->setValue(percent);
  val->setText(QString("%1%").arg(percent));
  update();
}

void Installer::doInstall() {
  // wait for valid time
  while (!util::system_time_valid()) {
    usleep(500 * 1000);
    qDebug() << "Waiting for valid time";
  }

  // cleanup previous install attempts
  run("rm -rf " PATH_OP_INSTALL " " PATH_TSKM_GIT_CLONE " " PATH_RELEASE_GIT_CLONE " " PATH_NIGHTLY_GIT_CLONE " || true");

  // do the install
  freshClone();
}

void Installer::freshClone() {
  qDebug() << "Doing fresh clone";

  // Clone commaai/devel
  procGitCloneRelease.start("/usr/bin/git", {"clone", "--progress",
                     "https://github.com/" RELEASE_USER "/openpilot.git",
                     "-b", RELEASE_BRANCH, "--depth=1", "--recurse-submodules",
                     PATH_RELEASE_GIT_CLONE});

  // Clone commaai/nightly-dev
  procGitCloneNightly.start("/usr/bin/git", {"clone", "--progress",
                     "https://github.com/" NIGHTLY_USER "/openpilot.git",
                     "-b", NIGHTLY_BRANCH, "--depth=1", "--recurse-submodules",
                     PATH_NIGHTLY_GIT_CLONE});

  // Clone optskug/tskm-0.9.8
  procGitCloneTSKM.start("/usr/bin/git", {"clone", "--progress",
                     "https://github.com/" TSKM_USER "/openpilot.git",
                     "-b", TSKM_BRANCH, "--depth=1", "--recurse-submodules",
                     PATH_TSKM_GIT_CLONE});
}

void Installer::readProgress() {
  const QVector<QPair<QString, int>> stages = {
    // prefix, weight in percentage
    {"Receiving objects: ", 91},
    {"Resolving deltas: ", 2},
    {"Updating files: ", 7},
  };

  auto line = QString(procGitCloneNightly.readAllStandardError()); // Start with the biggest repo
  if (line.isEmpty()) {
      line = QString(procGitCloneRelease.readAllStandardError());
  }
  if (line.isEmpty()) {
      line = QString(procGitCloneTSKM.readAllStandardError());
  }

  int base = 0;
  for (const QPair kv : stages) {
    if (line.startsWith(kv.first)) {
      auto perc = line.split(kv.first)[1].split("%")[0];
      int p = base + int(perc.toFloat() / 100. * kv.second);
      updateProgress(p);
      break;
    }
    base += kv.second;
  }
}

void Installer::cloneReleaseFinishedHandler() {
  qDebug() << "git clone " RELEASE_USER "/" RELEASE_BRANCH " finished";
  cloneReleaseFinished = true;
  checkIfAllClonesFinished();
}

void Installer::cloneNightlyFinishedHandler() {
  qDebug() << "git clone " NIGHTLY_USER "/" NIGHTLY_BRANCH " finished";
  cloneNightlyFinished = true;
  checkIfAllClonesFinished();
}

void Installer::cloneTSKMFinishedHandler() {
  qDebug() << "git clone " TSKM_USER "/" TSKM_BRANCH " finished";
  cloneTSKMFinished = true;
  checkIfAllClonesFinished();
}

void Installer::checkIfAllClonesFinished() {
  if (cloneReleaseFinished && cloneNightlyFinished && cloneTSKMFinished) {
    // All clones are finished, proceed with the rest of the installation
    updateProgress(98); // Give it time to download the cache

    // move into place
    run("mv " PATH_TSKM_GIT_CLONE " " PATH_OP_INSTALL);

    // write continue.sh
    FILE *of = fopen("/data/continue.sh.new", "wb");
    assert(of != NULL);

    size_t num = str_continue_end - str_continue;
    size_t num_written = fwrite(str_continue, 1, num, of);
    assert(num == num_written);
    fclose(of);

    run("chmod +x /data/continue.sh.new");
    run("mv /data/continue.sh.new /data/continue.sh");

    // wait for the installed software's UI to take over
    QTimer::singleShot(60 * 1000, &QCoreApplication::quit);
  }
}

int main(int argc, char *argv[]) {
  initApp(argc, argv);
  QApplication a(argc, argv);
  Installer installer;
  setMainWindow(&installer);
  return a.exec();
}
