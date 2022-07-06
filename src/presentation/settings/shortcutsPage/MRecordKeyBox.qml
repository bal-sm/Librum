import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CustomComponents
import Qt5Compat.GraphicalEffects
import Librum.style
import Librum.icons
import Librum.QmlComponents


Item
{
    id: root
    property var itemToRedirectFocusTo
    property bool recording: false
    property string originalSequence: ""
    
    
    Glow
    {
        id: backgroundGlow
        visible: root.recording
        width: button.width
        height: button.height
        x: button.x
        y: button.y
        spread: 0
        transparentBorder: true
        z: -1
        color: "#A92224"
        
        source: button
    }
    
    ColumnLayout
    {
        id: mainLayout
        anchors.fill: parent
        spacing: 2
        
        Label
        {
            id: header
            text: "Key"
            font.weight: Font.DemiBold
            font.pointSize: 12
            font.family: Style.defaultFontFamily
            color: Style.colorBaseTitle
        }
        
        
        Rectangle
        {
            id: button
            
            Layout.fillWidth: true
            Layout.preferredHeight: 38
            radius: 4
            color: Style.colorBackground
            border.color: root.recording ? "#E8B9BA" : Style.colorLightBorder
            opacity: mouseArea.pressed ? 0.8 : 1
            
            onActiveFocusChanged: activeFocus ? root.startRecording() : root.stopRecording()
            
            
            KeySequenceRecorder
            {
                id: keySequenceRecorder
                originalSequence: root.originalSequence
                
                onCurrentSequenceChanged: recordLabel.text = currentSequence
            }
            
            
            RowLayout
            {
                id: contentLayout
                anchors.fill: parent
                spacing: 4
                
                
                Label
                {
                    id: recordLabel
                    Layout.fillWidth: true
                    Layout.leftMargin: 12
                    text: keySequenceRecorder.originalSequence === "" ? "Press to record" : keySequenceRecorder.originalSequence
                    font.pointSize: 13
                    font.family: Style.defaultFontFamily
                    color: Style.colorLightText3
                    elide: Text.ElideLeft
                }
                
                Image
                {
                    id: microphoneIcon
                    Layout.alignment: Qt.AlignRight
                    Layout.rightMargin: 12
                    source: root.recording ? Icons.active_microphone : Icons.microphone
                    sourceSize.width: 18
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }
    
    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        
        onClicked:
        {            
            if(root.recording)
            {
                stopRecording();
                root.forceActiveFocus();
                return;
            }
            
            startRecording();
            button.forceActiveFocus();
        }
    }
    
    
    SequentialAnimation
    {
        loops: Animation.Infinite
        id: buttonPulsatingAnimation
        
        
        PropertyAnimation
        {
            target: backgroundGlow
            property: "radius"
            duration: 600
            to: 16
        }
        
        PropertyAnimation
        {
            target: backgroundGlow
            property: "radius"
            duration: 600
            to: 2
        }
    }
    
    
    function startRecording()
    {
        keySequenceRecorder.forceActiveFocus();
        //        button.forceActiveFocus();
        root.recording = true;
        buttonPulsatingAnimation.start();
    }
    
    function stopRecording()
    {
        itemToRedirectFocusTo.forceActiveFocus();
        root.recording = false;
        buttonPulsatingAnimation.stop();
    }
}