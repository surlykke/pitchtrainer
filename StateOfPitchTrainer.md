# State of PitchTrainer #

!PitchTTrainer started out as a pure C++ application.

Lately work has been done to migrate the user-interface to QML using Qt-Quick 1.1 components. This means that PitchTrainer will run only on platforms with Qt >= 4.7.4 and QtQuick >= 1.1. These are

  * Harmattan 1.2. I.e. a Nokia 9, Nokia 950 or Scratchbox. Sofar Pitch-trainer has only been tested on Scratchbox, Harmattan target.
  * 'Standard Meego'. If there is such a thing. The intention is to make PitchTrainer run on Meego N900 CE.

Requirements:
  * PitchTrainer creates it's audio-output by forming midi-files, using WildMidi to transform those to pcm-files that are handed to PulseAudio. Therefore PitchTrainer depends on libwildmidi-dev for compiling and libwildmidi for execution.

Issues:
  * Currently I can't get audio-output working in scratchbox. I get some assertion failure in PA. There is a known issue with PA, Scratchbox and Ubuntu Natty (which I use), but I've tried the suggested work-around with no luck. So right now audio output is disabled in Pitch-trainer.