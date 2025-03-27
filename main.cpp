#include "hospital_management.hpp"

int main() {
    
    std::shared_ptr<Patient> patient = std::make_shared<Patient>("John Doe", 30);
    std::shared_ptr<Doctor> doctor = std::make_shared<Doctor>("Dr. Smith", "Cardiologist");
    std::shared_ptr<MedicalStaff> staff = std::make_shared<MedicalStaff>("Nurse Mari", "Nurse");

    
    std::shared_ptr<MedicalProcedure> surgery = std::make_shared<Surgery>();
    std::shared_ptr<MedicalProcedure> checkUp = std::make_shared<CheckUp>();

    
    std::shared_ptr<Appointment> appointment = std::make_shared<ConcreteAppointment>(patient, doctor, "2023-10-15 10:00");

    try {
        
        appointment->schedule();
        
        
        std::shared_ptr<Appointment> conflictingAppointment = std::make_shared<ConcreteAppointment>(patient, doctor, "2023-10-15 10:00");
        conflictingAppointment->schedule();  
    } catch (const SchedulingConflictException& e) {
        std::cout << e.what() << std::endl;
    }

    
    surgery->perform();
    patient->addProcedure("Heart Surgery");

    checkUp->perform();
    patient->addProcedure("Routine Check-Up");

    
    std::cout << "\nPatient's Medical History:" << std::endl;
    for (const auto& procedure : *patient) {
        std::cout << procedure << std::endl;
    }

    try {
        
        appointment->reschedule("2023-10-15 10:00");  
    } catch (const SchedulingConflictException& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        
        appointment->cancel();
    } catch (const PatientNotFoundException& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
