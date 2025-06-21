🏦 ATM Banking System :– 

This project simulates a complete ATM-Banking architecture, integrating embedded firmware,Linux-based ATM backend code, and a central banking application with file-based database interaction. It’s modular, scalable, and designed for both simulation and real-device testing (e.g., LPC2148).

---

📁 Project Structure

ATM-SYSTEM-DESIGN-WITH-DATABASE-INTEGRATION/
├── ATM/         # ATM backend logic written in C (Linux-based)
├── BANK/        # Central banking application (admin control, info, and DB)
├── FRIMWARE/    # Embedded firmware for LPC2148 (front-end interface)

---

🧠 Project Explanation

🔐  ATM/ – ATM Backend 
- User authentication via PIN  
- Balance inquiry, deposit, and withdrawal  
- File-based data interaction  
- Designed to run in a Linux environment

🧪 Build and Run:

cd ATM
make -f makeATM
./bank


🛠️ BANK/ – Central Bank Application
- Admin-side interface to manage:
  - Account creation, update, deletion
  - Transaction logs
  - Balance database
- Simulates backend DB interactions

🧪 Build and Run:

cd BANK
make -f makeBANK
./bank

📡 FRIMWARE/ – LPC2148 Frontend (Optional)
- Embedded C code for:
  - Keypad input (PIN, amount)
  - LCD display (welcome, processing, result)
  - UART communication with ATM backend  
- Flashable using Keil or Flash Magic

---

⌨ How to Run (Beginner Friendly)

1. Clone the Repository
   
   git clone https://github.com/saiduluneelam/ATM-SYSTEM-DESIGN-WITH-DATABASE-INTEGRATION.git
   cd ATM-SYSTEM-DESIGN-WITH-DATABASE-INTEGRATION
  

2. Install Build Tools
  
   sudo apt update
   sudo apt install build-essential

3. Compile and Run ATM Backend

   cd ATM
   make -f makeATM
   ./bank
  

4. Compile and Run Bank Application
   
   cd ../BANK
   make -f makeBANK
   ./bank
  

5. Load Firmware to LPC2148 (Optional)
   - Open Keil or Flash Magic  
   - Load hex/bin files from `FRIMWARE/`  
   - Flash to LPC2148  
   - Connect serial to ATM backend

---

📌 Notes
- Data is stored in simple, human-readable files for easy debugging.  
- The firmware module is optional and intended for LPC2148 hardware integration.  
- This project is modular and can be extended with networking or GUI features in the future.
