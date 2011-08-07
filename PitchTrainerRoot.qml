import QtQuick 1.1
import com.nokia.meego 1.0

Window {
    id: rootWindow

    PageStack {
        id: pageStack
    }

    PitchTrainerMain {
        id: pitchTrainerMain
    }

    PitchTrainerSettings {
        id: pitchTrainerSettings
    }

    Component.onCompleted: pageStack.push(pitchTrainerMain)


}
