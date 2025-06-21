
ATM System with RFID Authentication and Backend Database  
Project Overview  
This project implements a secure ATM system using RFID card authentication combined with PIN verification. The system comprises a front-end embedded microcontroller (LPC2148) interfaced with hardware modules, and a PC-side C application simulating the banking database using data structures and file handling. The communication between MCU and PC occurs over UART.

Hardware Components  
- LPC2148 Microcontroller  
- RFID Reader & RFID Cards (10-byte card number format)  
- 16x2 LCD Display for user interface  
- 4x4 Matrix Keypad for PIN and transaction input  
- MAX232 for UART level shifting  
- USB-to-UART converter/DB9 cable for PC communication  
- Buzzer for alerts  

Software Components  
- Embedded C for MCU programming (Keil uVision IDE, GCC compiler)  
- PC-side program in C (Linux) simulating banking database with linked lists and file handling  
- UART interrupt-based communication for MCU-PC interaction  

System Flow

1. Initialization  
- MCU initializes hardware modules (LCD, keypad, UART, RFID reader).  
- PC loads user and transaction data from files (users.txt, transactions.txt).  

2. Card Detection & Validation  
- User places RFID card near the reader; MCU reads card number.  
- MCU sends card number to PC: #CARD:12345678$.  
- PC validates card against database and replies:  
  - @OK#VALID_CARD$ if found  
  - @ERR#INVALID_CARD$ if not found  

3. PIN Verification  
- MCU prompts user for PIN input on keypad.  
- Sends #CARD:12345678#PIN:4321$ to PC.  
- PC validates PIN and responds:  
  - @OK#LOGIN_SUCCESS$ on success  
  - @ERR#INVALID_PIN$ on failure  

4. User Menu & Transactions  
- MCU displays menu on LCD:  
  1. Balance Enquiry  
  2. Deposit  
  3. Withdraw  
  4. PIN Change  
  5. Mini Statement  
  6. Exit  

- User selects an option via keypad; MCU sends corresponding request to PC:  
  - Balance: #TXN:BALANCE#REQ$  
  - Deposit: #TXN:DEPOSIT#AMOUNT:XXXX$  
  - Withdraw: #TXN:WITHDRAW#AMOUNT:XXXX$  
  - PIN Change: #PINCHANGE#NEWPIN$  
  - Mini Statement: #MINISTMT#REQ$  

5. Transaction Processing & Responses  
- PC processes request by updating user data and transaction logs, then sends responses:  
  - Successful balance update: @OK#BALANCE:XXXX.XX$  
  - Insufficient funds: @ERR#INSUFFICIENT_BALANCE$  
  - PIN change success/failure: @OK#PINCHANGED$ or @ERR#PINCHANGE_FAILED$  
  - Mini statement: @OK#MINISTMT:TXN1|TXN2|TXN3$ (last 3 transactions)  

- MCU displays messages accordingly and returns to waiting for new card or menu input.  

6. Timeout Handling  
- After showing the menu, if no keypad input is detected within 30 seconds, MCU resets to idle state, waiting for next card.

Data Structures Used (PC Side)  
- User  
typedef struct {  
    char tag_id[20];  
    char pin[10];  
    char name[50];  
    float balance;  
} User;  

- Transaction (linked list node)  
typedef struct Transaction {  
    char tag_id[20];  
    char type[10];    // Withdraw or Deposit  
    float amount;  
    char timestamp[25];  
    struct Transaction *next;  
} Transaction;  

UART Communication Formats  

| Direction       | Format Example                      | Description                       |  
|-----------------|-----------------------------------|---------------------------------|  
| MCU → PC        | #CARD:12345678$                 | Send RFID card number            |  
| MCU → PC        | #CARD:12345678#PIN:4321$        | Send card and PIN for login     |  
| MCU → PC        | #TXN:BALANCE#REQ$               | Request balance enquiry          |  
| MCU → PC        | #TXN:DEPOSIT#AMOUNT:1000$       | Request deposit                 |  
| MCU → PC        | #TXN:WITHDRAW#AMOUNT:500$       | Request withdrawal              |  
| MCU → PC        | #PINCHANGE#NEWPIN$              | Request PIN change               |  
| MCU → PC        | #MINISTMT#REQ$                  | Request mini statement           |  
| PC → MCU        | @OK#VALID_CARD$                 | Card validated                  |  
| PC → MCU        | @ERR#INVALID_CARD$              | Card invalid                   |  
| PC → MCU        | @OK#LOGIN_SUCCESS$              | PIN validated                  |  
| PC → MCU        | @ERR#INVALID_PIN$               | PIN invalid                   |  
| PC → MCU        | @OK#BALANCE:XXXX.XX$            | Balance info / transaction success |  
| PC → MCU        | @ERR#INSUFFICIENT_BALANCE$     | Insufficient funds              |  
| PC → MCU        | @OK#PINCHANGED$                 | PIN changed successfully        |  
| PC → MCU        | @ERR#PINCHANGE_FAILED$          | PIN change failed               |  
| PC → MCU        | @OK#MINISTMT:TXN1|TXN2|TXN3$    | Last 3 transactions             |  

Additional Notes  
- Transaction logs are maintained in linked lists and saved in files for persistence.  
- OTP verification can be implemented on MCU side for additional security when account numbers exceed 10 digits.  
- The system uses UART interrupts for asynchronous communication.  
- The PC program continuously listens for requests and processes accordingly.  
- The LCD displays clear prompts and transaction status messages for a smooth user experience.

How to Run  
1. Compile and upload MCU code (using Keil) to LPC2148.  
2. Run PC-side C application on Linux to simulate the backend database.  
3. Connect MCU and PC via UART (through MAX232 and USB-UART converter).  
4. Power the hardware, place RFID card, and follow on-screen instructions.

This README provides a comprehensive overview of the ATM system project architecture and flow. For detailed code references and hardware wiring, please refer to the respective source files and datasheets.
