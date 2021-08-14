#include "audiorecorder.h"

AudioRecorder::AudioRecorder()
{

}

bool AudioRecorder::onStart() { // optional
    // initialize whatever has to be done before the capture starts
    this->volume = 0;

    // return true to start the capture, or false to cancel it
    return true;
}

int AudioRecorder::getVolume() const
{
    return volume;
}

void AudioRecorder::setVolume(int value)
{
    volume = value;
}

// get the average volume of the collected samples
bool AudioRecorder::onProcessSamples(const sf::Int16* samples, std::size_t sampleCount) {
    int sum = 0;

    // loop through all samples since last call
    for (int i = 0; i < sampleCount; i++) {
        // since we are just looking at amplitude, the integers sign doesn't matter. Take the absolute value of the integer
        sum += abs(samples[i]);
    }

    int average = sum / sampleCount; // a float would be more accurate, but we are fine without the accuracy
    this->volume = average;

    // return true to continue the capture, or false to stop it
    return true;
}

void AudioRecorder::onStop() // optional
{
    // clean up whatever has to be done after the capture is finished

}
