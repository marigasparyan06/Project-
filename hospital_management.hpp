#ifndef HOSPITAL_MANAGEMENT_HPP
#define HOSPITAL_MANAGEMENT_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

class Doctor;
class Patient;
class Appointment;
class MedicalProcedure;
class Surgery;
class CheckUp;

class SchedulingConflictException : public std::exception {
public:
    const char* what() const noexcept override;
};

class PatientNotFoundException : public std::exception {
public:
    const char* what() const noexcept override;
};

class Patient {
private:
    std::string m_name;
    int m_age;
    std::vector<std::string> m_medicalHistory;

public:
    Patient(const std::string& name, int age);
    void addProcedure(const std::string& procedure);
    const std::vector<std::string>& getMedicalHistory() const;
    std::vector<std::string>::const_iterator begin() const;
    std::vector<std::string>::const_iterator end() const;
    std::string getName() const;
    int getAge() const;
};

class Doctor {
private:
    std::string m_name;
    std::string m_specialty;
    std::vector<std::string> m_appointments;

public:
    Doctor(const std::string& name, const std::string& specialty);
    std::string getName() const;
    std::string getSpecialty() const;
    void addAppointment(const std::string& appointment);
    bool doctorIsBusy(const std::string& reschedule_appointment) const;
};

class MedicalStaff {
private:
    std::string m_name;
    std::string m_position;

public:
    MedicalStaff(const std::string& name, const std::string& position);
    std::string getName() const;
    std::string getPosition() const;
};

class MedicalProcedure {
public:
    virtual ~MedicalProcedure() = default;
    virtual void perform() const = 0;
};

class Surgery : public MedicalProcedure {
public:
    void perform() const override;
};

class CheckUp : public MedicalProcedure {
public:
    void perform() const override;
};

class Appointment {
protected:
    std::shared_ptr<Patient> m_patient;
    std::shared_ptr<Doctor> m_doctor;
    std::string m_time;

public:
    Appointment(std::shared_ptr<Patient> patient, std::shared_ptr<Doctor> doctor, const std::string& time);
    virtual void schedule() = 0;
    virtual void reschedule(const std::string& newTime) = 0;
    virtual void cancel() = 0;
    std::string getTime();
};

class ConcreteAppointment : public Appointment {
public:
    ConcreteAppointment(std::shared_ptr<Patient> patient, std::shared_ptr<Doctor> doctor, const std::string& time);
    void schedule() override;
    void reschedule(const std::string& reschedule_time) override;
    void cancel() override;
};

template <typename T>
void printPatientData(const T& patientData) {
    for (const auto& entry : patientData) {
        std::cout << entry << std::endl;
    }
}

#include "hospital_management.cpp"

#endif 
