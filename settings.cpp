#include "settings.h"
#include "ui_settings.h"

Settings::Settings(int instrument, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{ 
    ui->setupUi(this);

    QStringList insts;
    insts   << "Acoustic Grand Piano"
            << "Bright Acoustic Piano"
            << "Electric Grand Piano"
            << "Honky-tonk Piano"
            << "Electric Piano 1"
            << "Electric Piano 2"
            << "Harpsichord"
            << "Clavinet"
            << "Celesta"
            << "Glockenspiel"
            << "Music Box"
            << "Vibraphone"
            << "Marimba"
            << "Xylophone"
            << "Tubular Bells"
            << "Dulcimer"
            << "Drawbar Organ"
            << "Percussive Organ"
            << "Rock Organ"
            << "Church Organ"
            << "Reed Organ"
            << "Accordion"
            << "Harmonica"
            << "Tango Accordion"
            << "Acoustic Guitar (nylon)"
            << "Acoustic Guitar (steel)"
            << "Electric Guitar (jazz)"
            << "Electric Guitar (clean)"
            << "Electric Guitar (muted)"
            << "Overdriven Guitar"
            << "Distortion Guitar"
            << "Guitar Harmonics"
            << "Acoustic Bass"
            << "Electric Bass (finger)"
            << "Electric Bass (pick)"
            << "Fretless Bass"
            << "Slap Bass 1"
            << "Slap Bass 2"
            << "Synth Bass 1"
            << "Synth Bass 2"
            << "Violin"
            << "Viola"
            << "Cello"
            << "Contrabass"
            << "Tremolo Strings"
            << "Pizzicato Strings"
            << "Orchestral Harp"
            << "Timpani"
            << "String Ensemble 1"
            << "String Ensemble 2"
            << "Synth Strings 1"
            << "Synth Strings 2"
            << "Choir Aahs"
            << "Voice Oohs"
            << "Synth Choir"
            << "Orchestra Hit"
            << "Trumpet"
            << "Trombone"
            << "Tuba"
            << "Muted Trumpet"
            << "French Horn"
            << "Brass Section"
            << "Synth Brass 1"
            << "Synth Brass 2"
            << "Soprano Sax"
            << "Alto Sax"
            << "Tenor Sax"
            << "Baritone Sax"
            << "Oboe"
            << "English Horn"
            << "Bassoon"
            << "Clarinet"
            << "Piccolo"
            << "Flute"
            << "Recorder"
            << "Pan Flute"
            << "Blown Bottle"
            << "Shakuhachi"
            << "Whistle"
            << "Ocarina";
    ui->instrumentBox->insertItems(0, insts);
    ui->instrumentBox->setCurrentIndex(instrument);
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(accept()));
}

Settings::~Settings()
{
    delete ui;
}

void Settings::backButtonClicked() {
    done(0);
}