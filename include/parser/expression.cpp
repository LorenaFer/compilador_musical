#include "expression.hpp"
#include <sstream>

extern bool yydebug;

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
    std::stringstream ss;
    ss << "Configuration(tempo_set: " << (tempo_set ? "true" : "false") 
       << ", time_signature_set: " << (time_signature_set ? "true" : "false")
       << ", key_set: " << (key_set ? "true" : "false");
    
    if (tempo_set) {
        ss << ", tempo: " << tempo_value;
    }
    
    if (time_signature_set) {
        ss << ", time_signature: " << time_signature_num << "/" << time_signature_den;
    }
    
    if (key_set) {
        ss << ", key: " << key_note << " " << key_mode;
    }
    
    ss << ")"s;
    return ss.str();
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
    if (bpm <= 0 && yydebug) {
        fprintf(stderr, "ERROR: El tempo debe ser positivo\n");
    }
    
    tempo_set = true;
    tempo_value = bpm;
    
    if (!yydebug) return;
    fprintf(stderr, "DEBUG: Configuración: tempo establecido a %d\n", bpm);
}

void Configuration::setTimeSignature(int numerator, int denominator) noexcept {
    if (numerator <= 0 && yydebug) {
        fprintf(stderr, "ERROR: El numerador del compás debe ser positivo\n");
    }
    if (denominator <= 0 && yydebug) {
        fprintf(stderr, "ERROR: El denominador del compás debe ser positivo\n");
    }
    
    time_signature_set = true;
    time_signature_num = numerator;
    time_signature_den = denominator;
    
    if (!yydebug) return;
    fprintf(stderr, "DEBUG: Configuración: compás establecido a %d/%d\n", numerator, denominator);
}

void Configuration::setKey(const std::string& note, const std::string& mode) noexcept {
    key_set = true;
    key_note = note;
    key_mode = mode;
    
    if (!yydebug) return;
    fprintf(stderr, "DEBUG: Configuración: tonalidad establecida a %s %s\n", note.c_str(), mode.c_str());
}

// Tempo
Tempo::Tempo(int bpm) noexcept : bpm(bpm) {
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
    : configuration(config) {
    if (!yydebug) return;
    fprintf(stderr, "DEBUG: Programa musical creado\n");
}

void MusicProgram::destroy() noexcept {
    if (configuration) {
        configuration->destroy();
        delete configuration;
        configuration = nullptr;
        
        if (!yydebug) return;
        fprintf(stderr, "DEBUG: Programa musical destruido\n");
    }
}

std::string MusicProgram::to_string() const noexcept {
    std::stringstream ss;
    ss << "MusicProgram(" << (configuration ? configuration->to_string() : "null") << ")";
    return ss.str();
}

bool MusicProgram::validate() const noexcept {
    return configuration && configuration->isComplete();
}

Configuration* MusicProgram::getConfiguration() const noexcept {
    return configuration;
}

// Note
Note::Note(const std::string& name, const std::string& alteration, int octave, const std::string& duration) noexcept
    : name(name), alteration(alteration), octave(octave), duration(duration) {
    if (!yydebug) return;
    fprintf(stderr, "DEBUG: Nota creada: %s%s%d con duración %s\n", 
            name.c_str(), alteration.c_str(), octave, duration.c_str());
}

void Note::destroy() noexcept {
    if (!yydebug) return;
    fprintf(stderr, "DEBUG: Nota destruida\n");
}

std::string Note::to_string() const noexcept {
    std::stringstream ss;
    ss << "Note(" << name;
    
    if (!alteration.empty()) {
        ss << alteration;
    }
    
    ss << octave << ", duration: " << duration << ")";
    return ss.str();
} 