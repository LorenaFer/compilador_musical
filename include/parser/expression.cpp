#include "expression.hpp"

using namespace std::literals;

// Expression
Expression::~Expression() {}

// Configuration
Configuration::Configuration() noexcept
    : tempo_set(false), time_signature_set(false), key_set(false),
      tempo_value(0), time_signature_num(0), time_signature_den(0),
      key_note(""), key_mode("") {}

void Configuration::destroy() noexcept {}

bool Configuration::isComplete() const noexcept {
    return tempo_set && time_signature_set && key_set;
}

std::string Configuration::to_string() const noexcept {
    std::string result = "Configuration(tempo_set: "s + (tempo_set ? "true" : "false") + 
                         ", time_signature_set: "s + (time_signature_set ? "true" : "false") +
                         ", key_set: "s + (key_set ? "true" : "false");
    
    if (tempo_set) {
        result += ", tempo: " + std::to_string(tempo_value);
    }
    
    if (time_signature_set) {
        result += ", time_signature: " + std::to_string(time_signature_num) + "/" + 
                 std::to_string(time_signature_den);
    }
    
    if (key_set) {
        result += ", key: " + key_note + " " + key_mode;
    }
    
    result += ")"s;
    return result;
}

bool Configuration::hasTempo() const noexcept {
    return tempo_set;
}

bool Configuration::hasTimeSignature() const noexcept {
    return time_signature_set;
}

bool Configuration::hasKey() const noexcept {
    return key_set;
}

void Configuration::setTempo(int bpm) noexcept {
    tempo_set = true;
    tempo_value = bpm;
}

void Configuration::setTimeSignature(int numerator, int denominator) noexcept {
    time_signature_set = true;
    time_signature_num = numerator;
    time_signature_den = denominator;
}

void Configuration::setKey(const std::string& note, const std::string& mode) noexcept {
    key_set = true;
    key_note = note;
    key_mode = mode;
}

// Tempo
Tempo::Tempo(int bpm) noexcept : bpm(bpm) {
    tempo_set = true;
    setTempo(bpm);
}

void Tempo::destroy() noexcept {
    Configuration::destroy();
}

std::string Tempo::to_string() const noexcept {
    return "Tempo("s + std::to_string(bpm) + ")"s;
}

int Tempo::getValue() const noexcept {
    return bpm;
}

// TimeSignature
TimeSignature::TimeSignature(int numerator, int denominator) noexcept
    : numerator(numerator), denominator(denominator) {
    time_signature_set = true;
    setTimeSignature(numerator, denominator);
}

void TimeSignature::destroy() noexcept {
    Configuration::destroy();
}

std::string TimeSignature::to_string() const noexcept {
    return "TimeSignature("s + std::to_string(numerator) + "/" + std::to_string(denominator) + ")"s;
}

int TimeSignature::getNumerator() const noexcept {
    return numerator;
}

int TimeSignature::getDenominator() const noexcept {
    return denominator;
}

// Key
Key::Key(const std::string& note, const std::string& mode) noexcept
    : note(note), mode(mode) {
    key_set = true;
    setKey(note, mode);
}

void Key::destroy() noexcept {
    Configuration::destroy();
}

std::string Key::to_string() const noexcept {
    return "Key("s + note + " " + mode + ")"s;
}

std::string Key::getNote() const noexcept {
    return note;
}

std::string Key::getMode() const noexcept {
    return mode;
}

// MusicProgram
MusicProgram::MusicProgram(Configuration* config) noexcept
    : configuration(config) {}

void MusicProgram::destroy() noexcept {
    if (configuration) {
        configuration->destroy();
        delete configuration;
        configuration = nullptr;
    }
}

std::string MusicProgram::to_string() const noexcept {
    return "MusicProgram("s + (configuration ? configuration->to_string() : "null") + ")"s;
}

bool MusicProgram::validate() const noexcept {
    return configuration && configuration->isComplete();
}

Configuration* MusicProgram::getConfiguration() const noexcept {
    return configuration;
}

// Note
Note::Note(const std::string& name, const std::string& alteration, int octave, const std::string& duration) noexcept
    : name(name), alteration(alteration), octave(octave), duration(duration) {}

void Note::destroy() noexcept {}

std::string Note::to_string() const noexcept {
    return "Note("s + name + alteration + std::to_string(octave) + " " + duration + ")"s;
} 