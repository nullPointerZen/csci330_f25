#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
#include <algorithm>

class MediaFile {
private:
    std::string filename;
    size_t file_size;

public:
    MediaFile(const std::string& name, size_t size)
        : filename(name), file_size(size) {
        std::cout << "Loaded media file: " << filename
                  << " (" << file_size << " bytes)" << std::endl;
    }

    ~MediaFile() {
        std::cout << "Unloaded media file: " << filename << std::endl;
    }

    const std::string& get_filename() const { return filename; }
    size_t get_size() const { return file_size; }

    void play() const {
        std::cout << "Playing: " << filename << std::endl;
    }
};

class Playlist {
private:
    std::string name;
    std::vector<std::shared_ptr<MediaFile>> files;

public:
    Playlist(const std::string& playlist_name) : name(playlist_name) {
        std::cout << "Created playlist: " << name << std::endl;
    }

    ~Playlist() {
        std::cout << "Destroyed playlist: " << name << std::endl;
    }

    void add_file(std::shared_ptr<MediaFile> file) {
        files.push_back(file);
        std::cout << "Added " << file->get_filename() << " to " << name << std::endl;
    }

    void play_all() const {
        std::cout << "Playing playlist: " << name << std::endl;
        for (const auto& file : files) {
            file->play();
        }
    }

    const std::string& get_name() const { return name; }
    size_t get_file_count() const { return files.size(); }
};

class MediaLibrary {
private:
    std::unordered_map<std::string, std::shared_ptr<MediaFile>> media_files;
    std::vector<std::unique_ptr<Playlist>> playlists;

public:
    std::shared_ptr<MediaFile> load_media_file(const std::string& filename, size_t size) {
        auto it = media_files.find(filename);
        if (it != media_files.end()) {
            return it->second;
        }
        auto file = std::make_shared<MediaFile>(filename, size);
        media_files[filename] = file;
        return file;
    }

    std::unique_ptr<Playlist> create_playlist(const std::string& name) {
        return std::make_unique<Playlist>(name);
    }

    void add_playlist_to_library(std::unique_ptr<Playlist> playlist) {
        playlists.push_back(std::move(playlist));
    }

    std::shared_ptr<MediaFile> get_media_file(const std::string& filename) {
        auto it = media_files.find(filename);
        return (it != media_files.end()) ? it->second : nullptr;
    }

    void show_library_status() const {
        std::cout << "\n=== Media Library Status ===" << std::endl;
        std::cout << "Media files: " << media_files.size() << std::endl;
        for (const auto& pair : media_files) {
            std::cout << "  " << pair.first << " (refs: "
                      << pair.second.use_count() << ")" << std::endl;
        }

        std::cout << "Playlists: " << playlists.size() << std::endl;
        for (const auto& playlist : playlists) {
            std::cout << "  " << playlist->get_name()
                      << " (" << playlist->get_file_count() << " files)" << std::endl;
        }
    }
};

class NowPlayingTracker {
private:
    std::weak_ptr<MediaFile> current_track;

public:
    void set_current_track(std::shared_ptr<MediaFile> track) {
        current_track = track;
    }

    void show_current_track() const {
        if (auto track = current_track.lock()) {
            std::cout << "Now playing: " << track->get_filename() << std::endl;
        } else {
            std::cout << "No track is currently playing (expired)" << std::endl;
        }
    }
};

int main() {
    MediaLibrary library;
    NowPlayingTracker tracker;

    std::cout << "=== Loading media files ===\n";
    auto song1 = library.load_media_file("song1.mp3", 4000000);
    auto song2 = library.load_media_file("song2.mp3", 3500000);
    auto song3 = library.load_media_file("song3.mp3", 4200000);

    std::cout << "\n=== Creating playlists ===\n";
    auto rock_playlist = library.create_playlist("Rock Hits");
    auto chill_playlist = library.create_playlist("Chill Vibes");

    rock_playlist->add_file(song1);
    rock_playlist->add_file(song3);
    chill_playlist->add_file(song2);
    chill_playlist->add_file(song1);  // Same file in multiple playlists

    library.add_playlist_to_library(std::move(rock_playlist));
    library.add_playlist_to_library(std::move(chill_playlist));

    library.show_library_status();

    std::cout << "\n=== Testing now playing tracker ===\n";
    tracker.set_current_track(song2);
    tracker.show_current_track();

    std::cout << "\n=== Removing local references ===\n";
    song1.reset();
    song2.reset();
    song3.reset();

    library.show_library_status();
    tracker.show_current_track();  // Should still work via playlists

    return 0;
}