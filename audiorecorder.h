#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H
#include <SFML/Audio.hpp>
#include <iostream>


class AudioRecorder : public sf::SoundRecorder {
public:
    AudioRecorder();
    virtual void onStop();
    virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
    virtual bool onStart();

    int getMaxVolume() const;
    void setMaxVolume(int value);

    int getVolume() const;
    void setVolume(int value);

private:
    int volume;
};

#endif // AUDIORECORDER_H
