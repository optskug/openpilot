# TSK Manager

## Background

### The Problem

comma.ai makes DIY ADAS devices. Older devices include the comma eon; current ones are comma three (C3, aka tici), comma threeX (C3X, aka tizi), and comma four (C4, aka mici). comma discontinued support for C3.

Not all cars work with comma. Some use FlexRay (e.g. BMW) instead of CAN/CAN-FD. Toyota added cryptographic signatures to CAN messages — comma can still read the bus but can't write because it can't generate valid signatures.

### The Hack

Willem, an ex-comma.ai employee, found a way to extract the security key from the EPS firmware on 2021-23 RAV4 Prime. The same hack works unmodified on 2021-23 Sienna Hybrid, and with modifications on Yaris. Details are in `/Users/calvin/GitRepos/docs/README.md`.

Willem's hack was a Python script run over SSH. Calvin built a GUI around it — that's TSK Manager (TSKM), living in `tsk/` in this repo.

### Calvin's Cars

- 2023 Sienna Hybrid — C3X
- 2023 Bolt EV 2LT (no ACC) — C4

### Architecture

- `tsk/main.py` dispatches based on device type (C3X vs C4)
- `tsk/c3/` — C3X code (maintenance mode, 1920x1080)
- `tsk/c4/` — C4 code (active development, 536x240)
- `tsk/common/` — shared code (extractor, key file manager, widget base)
- Run with `./c3x` or `./c4`; requires .venv

### The Rebasing Problem

comma devices use vertical phone LCD screens (C3/C3X are 1920x1080 portrait). comma wrote their own GUI libs to draw on the rotated screen — there's no way to use the display without going through their libs. They replaced Qt with RayLib, and rewrite these GUI libs constantly with zero backwards compatibility. TSKM has been rewritten 3+ times to keep up.

TSKM rebases on `nightly-dev` to stay current with AGNOS (the device OS). This is necessary because:

- AGNOS updates are ~1GB and take ~10 minutes
- The key extraction process is already stressful for users (removing camera housing, running the extractor, hoping the car still drives)
- Adding an AGNOS update mid-process is a terrible experience
- Some users have poor connectivity (rural US)

The goal: user installs the TSKM branch at home, AGNOS updates while on Wi-Fi, then they drive to do the extraction with everything already current.

SunnyPilot's SunnyLink integration is a potential long-term path to avoid the rebasing entirely.

### SSH / Device Tips

- tmux detach on comma devices: backtick (`` ` ``) then `d`

### comma Release Branches

Each device family has its own release branch:

- C3X (tizi): `release-tizi`
- C4 (mici): `release-mici`
- C3 (tici): `release-tici` (no longer supported)
- `release3` is an older legacy device-agnostic branch

### Versioned Branches

Each release is tagged as a branch (e.g. `tskm-0.10.4`, `tskm-0.10.2`, `tskm-0.9.8`). These were meant to be frozen fallbacks, but comma's changes can break even old branches.

---

## Journal

When the user says "update the journal", write a summary of what was done in the current session into the journal below.

### 2025-11-15
Released TSK Manager v0.10.4 (latest commit on `tskm` branch).

### 2026-04-09
Current status: **fixed and verified end-to-end in car**.
- Latest `tskm` branch had a Panda error; older `tskm-0.10.2` also broken (three stripes black/gray/white screen).
- Diagnosed: `RuntimeError: CAN packet version mismatch` — the panda firmware is stale because TSKM kills boardd/pandad before they can flash it. The panda's `can_version` (firmware) doesn't match `CAN_PACKET_VERSION` (library). Different tskm versions show different library values: older tskm hardcoded `4`, current tskm uses `compute_version_hash()` which produces `1974202998`.
- Fix: added `panda.flash()` to `TSKExtractor.hack()` right after `panda = Panda()` in `tsk/common/extractor.py`. The `up_to_date()` guard makes it safe to call every run (no-ops in 0.0s if current). C3X uses the same `tsk.common.extractor`, so the fix covers both devices.
- Flash takes ~2.8s, no network required (firmware bundled locally). Reversible — when user installs nightly-dev/sunnypilot afterwards, pandad's signature check will reflash to that branch's version.
- End-to-end test passed: install release3 → panda flashed to release3 firmware (`can_version=4`) → install pre-fix tskm → got mismatch error as expected → install post-fix tskm → `panda.flash()` ran, extractor proceeded all the way to writing SecOC key to `/data/params/d/SecOCKey`.
- Bonus fix: `launch_chffrplus.sh` had an active `bash  # Debug` line between `python3 tsk/main.py` and `sudo reboot`, which left the device in a debug shell after the user clicked "Install nightly-dev" instead of auto-rebooting. Commented it out so the install→reboot flow works end-to-end.

### 2026-04-10
Two users reported successful key extraction using `calvinpark/tskm` — fix confirmed in the wild. Plan: squash the tskm branch to a single commit and push to `optskug/tskm` to ship it.
