#include "hospital_management.hpp"
#include <iostream>

int main() {
    
    Patient patient("Alex", 30);
    Doctor doctor("Dr. Max", "Surgeon");
    MedicalStaff staff("Mari", "Nurse");
    
    Surgery surgery;
    CheckUp checkUp;

    try {
        
        ConcreteAppointment appointment(&patient, &doctor, "10:00 AM");
        appointment.schedule();

        ConcreteAppointment anotherAppointment(&patient, &doctor, "10:00 AM");
        anotherAppointment.schedule();  

    } catch (const SchedulingConflictException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    try {
        
        surgery.perform();
        patient.addProcedure("Surgery");

        
        checkUp.perform();
        patient.addProcedure("CheckUp");

        
        std::cout << "Patient's Medical History:" << std::endl;
        for (const auto& procedure : patient) {
            std::cout << "- " << procedure << std::endl;
        }

    } catch (const PatientNotFoundException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
