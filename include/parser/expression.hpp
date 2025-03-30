#pragma once

#include <string>

class Expression {
public:
    virtual ~Expression();
    virtual void destroy() noexcept = 0;
    virtual std::string to_string() const noexcept = 0;
};

class Configuration : public Expression {
public:
    Configuration() noexcept;
    void destroy() noexcept override;
    bool isComplete() const noexcept;
    std::string to_string() const noexcept override;

    bool hasTempo() const noexcept;
    bool hasTimeSignature() const noexcept;
    bool hasKey() const noexcept;
    
    // Métodos para actualizar propiedades
    void setTempo(int bpm) noexcept;
    void setTimeSignature(int numerator, int denominator) noexcept;
    void setKey(const std::string& note, const std::string& mode) noexcept;

protected:
    bool tempo_set;
    bool time_signature_set;
    bool key_set;
    
    // Valores almacenados
    int tempo_value;
    int time_signature_num;
    int time_signature_den;
    std::string key_note;
    std::string key_mode;
};

class Tempo : public Configuration {
public:
    Tempo(int bpm) noexcept;
    void destroy() noexcept override;
    std::string to_string() const noexcept override;
    int getValue() const noexcept;

private:
    int bpm;
};

class TimeSignature : public Configuration {
public:
    TimeSignature(int numerator, int denominator) noexcept;
    void destroy() noexcept override;
    std::string to_string() const noexcept override;
    int getNumerator() const noexcept;
    int getDenominator() const noexcept;

private:
    int numerator;
    int denominator;
};

class Key : public Configuration {
public:
    Key(const std::string& note, const std::string& mode) noexcept;
    void destroy() noexcept override;
    std::string to_string() const noexcept override;
    std::string getNote() const noexcept;
    std::string getMode() const noexcept;

private:
    std::string note;
    std::string mode;
};

class MusicProgram : public Expression {
public:
    MusicProgram(Configuration* config) noexcept;
    void destroy() noexcept override;
    std::string to_string() const noexcept override;
    bool validate() const noexcept;
    Configuration* getConfiguration() const noexcept;

private:
    Configuration* configuration;
};

class Note : public Expression {
public:
    Note(const std::string& name, const std::string& alteration, int octave, const std::string& duration) noexcept;
    void destroy() noexcept override;
    std::string to_string() const noexcept override;

private:
    std::string name;
    std::string alteration;
    int octave;
    std::string duration;
}; 