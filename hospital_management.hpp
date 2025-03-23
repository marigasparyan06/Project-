#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <exception>
#include <string>
#include <vector>

class Patient {
private:
	std::string m_name;
	int m_age;
	std::vector<std::string> m_medicalHistory;
public:
	Patient(const std::string&, int);
	void addProcedure(const std::string&);
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
	Doctor(const std::string&, const std::string&);
	std::string getName() const;
	std::string getSpecialty() const;
	bool doctorIsBusy(Doctor*, const std::string&);
	void addAppointment(std::string&);

};

class MedicalStaff {
private:
	std::string m_name;
	std::string m_position;
public:
	MedicalStaff(const std::string&, const std::string&);
	std::string getName() const;
	std::string getPosition() const;
};

class MedicalProcedure {
public:
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
	Patient* m_patient;
	Doctor* m_doctor;
	std::string m_time;
public:
	Appointment(Patient*, Doctor*, const std::string&);
	virtual void schedule() = 0;
	virtual void reschedule(const std::string&) = 0;
	virtual void cancel() = 0;
	virtual std::string getTime() = 0;
};

class ConcreteAppointment : public Appointment {
public:
	ConcreteAppointment(Patient* patient, Doctor* doctor, const std::string& name) : Appointment(patient, doctor, name){}
	void schedule() override;
	void reschedule(const std::string&) override;
	void cancel() override;
	std::string getTime() override;
};

class SchedulingConflictException : public std::exception {
public:
    const char* what() const noexcept override;
};

class PatientNotFoundException : public std::exception {
public:
    const char* what() const noexcept override;
};

#include "hospital_management.cpp"
#endif //HEADER_HPP