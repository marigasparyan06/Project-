#include "hospital_management.hpp"


Patient::Patient(const std::string& name, int age) : m_name{name}, m_age{age} {}

void Patient::addProcedure(const std::string& procedure) {
    m_medicalHistory.push_back(procedure);
}

const std::vector<std::string>& Patient::getMedicalHistory() const {
    return m_medicalHistory;
}

std::vector<std::string>::const_iterator Patient::begin() const {
    return m_medicalHistory.cbegin();
}

std::vector<std::string>::const_iterator Patient::end() const {
    return m_medicalHistory.cend();
}

std::string Patient::getName() const {
    return m_name;
}
        
int Patient::getAge() const {
    return m_age;
}


Doctor::Doctor(const std::string& name, const std::string& specialty) : m_name{name}, m_specialty{specialty} {}

std::string Doctor::getName() const {
    return m_name;
}

std::string Doctor::getSpecialty() const {
    return m_specialty;
}

void Doctor::addAppointment(const std::string& appointment) {
    m_appointments.push_back(appointment);
}

bool Doctor::doctorIsBusy(const std::string& reschedule_appointment) const {
    for (const auto& app : m_appointments) {
        if (reschedule_appointment == app) {
            return true;
        }
    }
    return false;
}


MedicalStaff::MedicalStaff(const std::string& name, const std::string& position) : m_name{name}, m_position{position} {}

std::string MedicalStaff::getName() const {
    return m_name;
}

std::string MedicalStaff::getPosition() const {
    return m_position;
}


void Surgery::perform() const {
    std::cout << "Performing surgery..." << std::endl;
}


void CheckUp::perform() const {
    std::cout << "Performing check-up..." << std::endl;
}


Appointment::Appointment(std::shared_ptr<Patient> patient, std::shared_ptr<Doctor> doctor, const std::string& time) 
    : m_patient{patient}, m_doctor{doctor}, m_time{time} {}

std::string Appointment::getTime() {
    return m_time;
}


ConcreteAppointment::ConcreteAppointment(std::shared_ptr<Patient> patient, std::shared_ptr<Doctor> doctor, const std::string& time) 
    : Appointment{patient, doctor, time} {}

void ConcreteAppointment::schedule() {
    if (m_doctor->doctorIsBusy(m_time)) {
        throw SchedulingConflictException();
    }
    m_doctor->addAppointment(m_time);
    std::cout << "Appointment scheduled for " << m_patient->getName() << " at " << m_time << std::endl;
}

void ConcreteAppointment::reschedule(const std::string& reschedule_time) {
    if (m_doctor->doctorIsBusy(reschedule_time)) {
        throw SchedulingConflictException();
    }
    m_time = reschedule_time;
    std::cout << "Appointment rescheduled for " << m_patient->getName() << " at " << m_time << std::endl;
}

void ConcreteAppointment::cancel() {
    if (!m_patient || !m_doctor) {
        throw PatientNotFoundException();
    }
    std::cout << "Appointment canceled for " << m_patient->getName() << " at " << m_time << std::endl;
}


const char* SchedulingConflictException::what() const noexcept {
    return "Scheduling conflict detected!";
}

const char* PatientNotFoundException::what() const noexcept {
    return "Patient not found!";
}
