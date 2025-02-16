#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <map>
#include <string>
#include <raylib.h>
#include <raymath.h>

struct ActiveSound { //for positional audio
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

    void LoadVoice(const std::string& name, std::string filePath) {
        if (voices.find(name) == voices.end()) { //if name not in map, add it. If find(name) can't find it, it returns .end()
            Sound sound = ::LoadSound(filePath.c_str());
            voices[name] = sound; //store voice in array
        }
    }

    void LoadRobotVoice(const std::string& name, std::string filepath) {
        if (robotVoices.find(name) == robotVoices.end()) {
            Sound sound = ::LoadSound(filepath.c_str());
            robotVoices[name] = sound;
        }
    }

    // Load a sound and store it in the manager
    void LoadSound(const std::string& name, const std::string& filePath) {
        if (sounds.find(name) == sounds.end()) {//key doesn't exist in the map, so add it. 
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

    //Retrieve a voice by name
    Sound& GetVoice(const std::string& name) {
        return voices[name];
    }

    Sound& GetRobotVoice(const std::string& name) {
        return robotVoices[name];
    }

    void PlayRandomVoice() { //Play a single random clip
        if (voices.empty()) return; // Ensure there are voices loaded

        // Generate a random index
        int randomIndex = rand() % voices.size();
        
        // Iterate through the map to get the voice at the random index
        auto it = voices.begin();
        std::advance(it, randomIndex);

        // Play the sound
        ::PlaySound(it->second);
    }

    void PlayerRandomRobotVoice() {
        if (robotVoices.empty()) return;

        int randomIndex = rand() % robotVoices.size();

        auto it = robotVoices.begin();
        std::advance(it, randomIndex);

        ::PlaySound(it->second);
    }

    void PlayNextVoice() { //play a randomized series of clips. 
        if (voices.empty()) return;

        // Select a random voice
        int randomIndex = rand() % voices.size();
        auto it = voices.begin(); //asign the first sound.
    

        std::advance(it, randomIndex); //advance to random index 
        
        
        // Set current voice and play it
        currentVoice = it->second; //second means the value, in a key value pair. 
        ::PlaySound(currentVoice);
        voicePlaying = true;
    }




    void StartRandomVoices(float duration) { // start playing a randomized series of clips
        if (voices.empty()) return;

        voiceTimer = duration;
        PlayNextVoice();
    }

    void UpdateRandomVoices(float deltaTime) {
        if (voiceTimer <= 0.0f) {
            voicePlaying = false;
            return; // Stop if timer is up
        }

        voiceTimer -= deltaTime;

        // Check if the current voice is finished
        if (voicePlaying && !::IsSoundPlaying(currentVoice)) { //check every frame until current voice ended, play next voice
            voicePlaying = false; //stop playing before playing next voice. 
            PlayNextVoice(); // Play the next random voice
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

    void ManagerStopSound(const std::string& name){
        if (sounds.find(name) != sounds.end()){
            StopSound(sounds[name]);
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

    void UnloadAllSounds() { //with safety checks, was causing seg fault on close
        // Unload all sound effects
        for (auto& pair : sounds) {
            if (pair.second.frameCount > 0) {  // Ensure the sound is valid before unloading
                UnloadSound(pair.second);
            }
        }
        sounds.clear();

        // Unload all music streams
        for (auto& pair : musicTracks) {
            StopMusicStream(pair.second);  // Ensure it's stopped before unloading
            UnloadMusicStream(pair.second);
        }
        musicTracks.clear();
        
        //unload voices
        for (auto& pair : voices){
            if (pair.second.frameCount >0){
                UnloadSound(pair.second);
            }
        }
        voices.clear();

        //unload robot voices
        for (auto& pair : robotVoices) {
            if (pair.second.frameCount > 0){
                UnloadSound(pair.second);
            }
        }
        robotVoices.clear();

        activeSounds.clear();




    }


private:
    Sound currentVoice;        // The currently playing voice
    bool voicePlaying = false; // Track if a voice is currently playing
    float voiceTimer = 0.0f;   // Timer for the voice-playing sequence

    std::vector<ActiveSound> activeSounds;
    std::map<std::string, Sound> sounds; //array of sounds 
    std::map<std::string, Music> musicTracks;  // array of music tracks
    std::map<std::string, Sound> voices; //array of voices
    std::map<std::string, Sound> robotVoices; //array of robot noises

    // Make constructor private to enforce Singleton pattern
    SoundManager() = default;
    ~SoundManager() {
        UnloadAllSounds();
    }

    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;
};

#endif // SOUNDMANAGER_H
