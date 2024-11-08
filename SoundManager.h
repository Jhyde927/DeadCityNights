#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <map>
#include <string>
#include <raylib.h>
#include <raymath.h>

struct ActiveSound {
    Sound sound;
    Vector2 position;
    float maxDistance;
};

class SoundManager {
public:
    static SoundManager& getInstance() {
        static SoundManager instance;
        return instance;
    }

    // Load a sound and store it in the manager
    void LoadSound(const std::string& name, const std::string& filePath) {
        if (sounds.find(name) == sounds.end()) {
            Sound sound = ::LoadSound(filePath.c_str());  // Load the sound
            sounds[name] = sound;  // Store in the map
        }
    }

    // Load music and store it in the manager
    void LoadMusic(const std::string& name, const std::string& filePath) {
        if (musicTracks.find(name) == musicTracks.end()) {
            Music music = ::LoadMusicStream(filePath.c_str());  // Load the music stream
            musicTracks[name] = music;  // Store in the map
        }
    }

    // Retrieve a sound by name
    Sound& GetSound(const std::string& name) {
        return sounds[name];
    }

    // Retrieve music by name
    Music& GetMusic(const std::string& name) {
        return musicTracks[name];
    }


    void PlaySoundAtPosition(const std::string& name, float sourceX, float listenerX, float maxDistance) {
        if (sounds.find(name) != sounds.end()) {
            float volume = CalculateVolume(sourceX, listenerX, maxDistance);
            ::SetSoundVolume(sounds[name], volume);
            ::PlaySound(sounds[name]);
            std::cout << "adjusting Volume";
        }
    }


    // Play music with looping enabled
    void PlayMusic(const std::string& name) {
        if (musicTracks.find(name) != musicTracks.end()) {
            PlayMusicStream(musicTracks[name]);
            musicTracks[name].looping = true;  // Set looping
        }
    }

    // Stop all music
    void StopMusic(const std::string& name) {
        if (musicTracks.find(name) != musicTracks.end()) {
            StopMusicStream(musicTracks[name]);
        }
    }



    // Update music stream (call every frame to keep it playing)
    void UpdateMusic(const std::string& name) {
        if (musicTracks.find(name) != musicTracks.end()) {
            UpdateMusicStream(musicTracks[name]);
        }
    }

    void SetSoundVolume(const std::string& name, float volume) {
        if (sounds.find(name) != sounds.end()) {
            ::SetSoundVolume(sounds[name], volume);  // Set volume of the sound
        }
    }

    void SetMusicVolume(const std::string& name, float volume) {
        if (musicTracks.find(name) != musicTracks.end()) {
            ::SetMusicVolume(musicTracks[name], volume);  // Set volume of the music stream
        }
    }

    // **New method to check if music is playing**
    bool IsMusicPlaying(const std::string& name) {
        if (musicTracks.find(name) != musicTracks.end()) {
            return ::IsMusicStreamPlaying(musicTracks[name]);
        }
        return false;  // Music track not found or not playing
    }

    bool IsSoundPlaying(const std::string& name) {
        if (sounds.find(name) != sounds.end()) {
            return ::IsSoundPlaying(sounds[name]);
        }
        return false;  // Music track not found or not playing
    }

    // **Optional: Pause and resume music methods**
    void PauseMusic(const std::string& name) {
        if (musicTracks.find(name) != musicTracks.end()) {
            ::PauseMusicStream(musicTracks[name]);
        }
    }

    void ResumeMusic(const std::string& name) {
        if (musicTracks.find(name) != musicTracks.end()) {
            ::ResumeMusicStream(musicTracks[name]);
        }
    }


    // Modified PlayPositionalSound to store active sounds
    void PlayPositionalSound(const std::string& name, Vector2 soundPos, Vector2 listenerPos, float maxDistance) {
        if (sounds.find(name) != sounds.end()) {
            Sound& sound = sounds[name];

            // Calculate initial volume
            float dx = listenerPos.x - soundPos.x;
            float dy = listenerPos.y - soundPos.y;
            float distance = sqrtf(dx * dx + dy * dy);
            float volume = 1.0f - (distance / maxDistance);
            if (volume < 0.0f) volume = 0.0f;
            ::SetSoundVolume(sound, volume);

            // Play the sound
            ::PlaySound(sound);

            // Add to active sounds
            ActiveSound activeSound = { sound, soundPos, maxDistance };
            activeSounds.push_back(activeSound);
        }
    }

    // Update method to be called each frame
    void UpdatePositionalSounds(Vector2 listenerPos) {
        for (auto it = activeSounds.begin(); it != activeSounds.end(); ) {
            // Update volume based on current listener position
            float dx = listenerPos.x - it->position.x;
            float dy = listenerPos.y - it->position.y;
            float distance = sqrtf(dx * dx + dy * dy);
            float volume = 1.0f - (distance / it->maxDistance);
            if (volume < 0.0f) volume = 0.0f;
            ::SetSoundVolume(it->sound, volume);

            // Remove sound from active list if it's no longer playing
            if (!::IsSoundPlaying(it->sound)) {
                it = activeSounds.erase(it);
            } else {
                ++it;
            }
        }
    }



    void UnloadAllSounds() {
        for (auto& pair : sounds) {
            if (pair.second.stream.buffer != nullptr) {  // Ensure the sound buffer is not null
                UnloadSound(pair.second);
            }
        }
        sounds.clear();
        
        for (auto& pair : musicTracks) {
            UnloadMusicStream(pair.second);  // Unload all music streams
        }
        musicTracks.clear();
    }

private:

    float CalculateVolume(float sourceX, float listenerX, float maxDistance) {
        float distance = std::fabs(sourceX - listenerX);
        float volume = 1.0f - (distance / maxDistance);
        if (volume < 0.0f) volume = 0.0f;
        return volume;
    }


    std::vector<ActiveSound> activeSounds;
    std::map<std::string, Sound> sounds; // vector of sounds?
    std::map<std::string, Music> musicTracks;  // Map for storing music streams

    // Make constructor private to enforce Singleton pattern
    SoundManager() = default;
    ~SoundManager() {
        UnloadAllSounds();
    }

    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;
};

#endif // SOUNDMANAGER_H
