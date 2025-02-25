#pragma once

#include <QLabel>
#include <QProcess>
#include <QProgressBar>
#include <QWidget>

class Installer : public QWidget {
  Q_OBJECT

public:
  explicit Installer(QWidget *parent = 0);

private slots:
  void updateProgress(int percent);

  void readProgress();
  void cloneReleaseFinishedHandler();
  void cloneNightlyFinishedHandler();
  void cloneTSKMFinishedHandler();

private:
  QLabel *val;
  QProgressBar *bar;
  QProcess procGitCloneRelease;
  QProcess procGitCloneNightly;
  QProcess procGitCloneTSKM;
  bool cloneReleaseFinished = false;
  bool cloneNightlyFinished = false;
  bool cloneTSKMFinished = false;

  void doInstall();
  void freshClone();
  void checkIfAllClonesFinished();
};
