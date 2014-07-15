/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "include/cef_app.h"



//==============================================================================
Cefaudio2AudioProcessor::Cefaudio2AudioProcessor()
{
}

Cefaudio2AudioProcessor::~Cefaudio2AudioProcessor()
{
}

//==============================================================================
const String Cefaudio2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int Cefaudio2AudioProcessor::getNumParameters()
{
    return 0;
}

float Cefaudio2AudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void Cefaudio2AudioProcessor::setParameter (int index, float newValue)
{
}

const String Cefaudio2AudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String Cefaudio2AudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String Cefaudio2AudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String Cefaudio2AudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool Cefaudio2AudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool Cefaudio2AudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool Cefaudio2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Cefaudio2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Cefaudio2AudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double Cefaudio2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Cefaudio2AudioProcessor::getNumPrograms()
{
    return 0;
}

int Cefaudio2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Cefaudio2AudioProcessor::setCurrentProgram (int index)
{
}

const String Cefaudio2AudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void Cefaudio2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Cefaudio2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    // Specify CEF global settings here.
    CefMainArgs main_args();
    CefSettings settings;
    CefRefPtr<CefApp> app();
    
    CefRunMessageLoop();
    
    
    // Initialize CEF for the browser process.
    //    CefInitialize(cef_main_args, settings, app.get(), NULL);
//    CefInitialize(main_args, settings&, app.get(), NULL);
}

void Cefaudio2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void Cefaudio2AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    static double phase = 0;
    
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getSampleData (channel);
        
        // ..do something to the data...
        for (int n = 0; n < buffer.getNumSamples(); n++) {
            
            if (channel == 0) { // increment phase once per sample
                
                phase += M_PI*2*880/getSampleRate(); // modulate by 880 Hz
                
                if (phase > 2*M_PI)
                    phase -= 2*M_PI;
            }
            
            channelData[n] *= sin(phase);
        }
    }
    
    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool Cefaudio2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Cefaudio2AudioProcessor::createEditor()
{
    return new Cefaudio2AudioProcessorEditor (this);
}

//==============================================================================
void Cefaudio2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Cefaudio2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Cefaudio2AudioProcessor();
}
