/*
 * Init_Sens.h
 *
 *  Created on: 09-Jun-2021
 *      Author: Suraj K
 */

#define PRINT_SKIP_COUNT        5

#define MPU9150_I2C_ADDRESS     0x68


uint32_t ui32SysClock;
tI2CMInstance g_sI2CInst;
tMPU9150 g_sMPU9150Inst;
uint32_t g_ui32PrintSkipCounter;
uint_fast32_t ui32Idx;

float pfData[3];
float *pfAccel;
char cSign[3];
int_fast32_t i32IPart[3], i32FPart[3];

volatile uint_fast8_t g_vui8I2CDoneFlag;
volatile uint_fast8_t g_vui8DataFlag;
volatile uint_fast8_t g_vui8ErrorFlag;

/////-------Declaring Functions--------/////
void MPU9150AppCallback(void*,uint_fast8_t);
void IntGPIOb(void);
void MPU9150I2CIntHandler(void);
void MPU9150AppErrorHandler(char *, uint_fast32_t);
void MPU9150AppI2CWait(char *, uint_fast32_t);
void ConfigureUART(void);
void init_mpu_i2c(void);

//*****************************************************************************
//
// MPU9150 Sensor callback function.  Called at the end of MPU9150 sensor
// driver transactions. This is called from I2C interrupt context. Therefore,
// we just set a flag and let main do the bulk of the computations and display.
//
//*****************************************************************************
void
MPU9150AppCallback(void *pvCallbackData, uint_fast8_t ui8Status)
{
    //
    // If the transaction succeeded set the data flag to indicate to
    // application that this transaction is complete and data may be ready.
    //
    if(ui8Status == I2CM_STATUS_SUCCESS)
    {
        g_vui8I2CDoneFlag = 1;

    }

    //
    // Store the most recent status in case it was an error condition
    //
    g_vui8ErrorFlag = ui8Status;
}
//*****************************************************************************
//
// Called by the NVIC as a result of GPIO port B interrupt event. For this
// application GPIO port B pin 2 is the interrupt line for the MPU9150
//
//*****************************************************************************
void
IntGPIOb(void)
{
    unsigned long ulStatus;

    ulStatus = GPIOIntStatus(GPIO_PORTB_BASE, true);

    //
    // Clear all the pin interrupts that are set
    //
    GPIOIntClear(GPIO_PORTB_BASE, ulStatus);

    if(ulStatus & GPIO_PIN_2)
    {
        //
        // MPU9150 Data is ready for retrieval and processing.
        //
        MPU9150DataRead(&g_sMPU9150Inst, MPU9150AppCallback, &g_sMPU9150Inst);
    }
}

//*****************************************************************************
//
// Called by the NVIC as a result of I2C3 Interrupt. I2C3 is the I2C connection
// to the MPU9150.
//
//*****************************************************************************
void
MPU9150I2CIntHandler(void)
{
    //
    // Pass through to the I2CM interrupt handler provided by sensor library.
    // This is required to be at application level so that I2CMIntHandler can
    // receive the instance structure pointer as an argument.
    //
    I2CMIntHandler(&g_sI2CInst);
}
//*****************************************************************************
//
// MPU9150 Application error handler. Show the user if we have encountered an
// I2C error.
//
//*****************************************************************************
void
MPU9150AppErrorHandler(char *pcFilename, uint_fast32_t ui32Line)
{
    //
    // Set terminal color to red and print error status and locations
    //
    UARTprintf("\033[31;1m");
    UARTprintf("Error: %d, File: %s, Line: %d\n"
               "See I2C status definitions in sensorlib\\i2cm_drv.h\n",
               g_vui8ErrorFlag, pcFilename, ui32Line);

    //
    // Return terminal color to normal
    //
    UARTprintf("\033[0m");

    //


    //
    // Go to sleep wait for interventions.  A more robust application could
    // attempt corrective actions here.
    //
    while(1)
    {
        //
        // Do Nothing
        //
    }
}
//*****************************************************************************
//
// Function to wait for the MPU9150 transactions to complete. Use this to spin
// wait on the I2C bus.
//
//*****************************************************************************
void
MPU9150AppI2CWait(char *pcFilename, uint_fast32_t ui32Line)
{
    //
    // Put the processor to sleep while we wait for the I2C driver to
    // indicate that the transaction is complete.
    //
    while((g_vui8I2CDoneFlag == 0) && (g_vui8ErrorFlag == 0))
    {
        //
        // Do Nothing
        //
    }

    //
    // If an error occurred call the error handler immediately.
    //
    if(g_vui8ErrorFlag)
    {
        MPU9150AppErrorHandler(pcFilename, ui32Line);
    }

    //
    // clear the data flag for next use.
    //
    g_vui8I2CDoneFlag = 0;
}

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}


//*****************************************************************************
//
// Initialize I2C for Sens Hub.
//
//*****************************************************************************
void init_mpu_i2c(void){

    pfAccel = pfData;

        MAP_SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                               SYSCTL_OSC_MAIN);

        // Enable port B used for motion interrupt.
        //
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

        ConfigureUART();

        UARTprintf("\033[2JMPU9150 Raw Example\n");


        // The I2C2 peripheral must be enabled before use.

        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2);
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

        // Configure the pin muxing for I2C3 functions on port E4 and E5.

            MAP_GPIOPinConfigure(GPIO_PE4_I2C2SCL);
            MAP_GPIOPinConfigure(GPIO_PE5_I2C2SDA);

        // Select the I2C function for these pins.  This function will also
        // configure the GPIO pins pins for I2C operation, setting them to
        // open-drain operation with weak pull-ups.  Consult the data sheet
        // to see which functions are allocated per pin.
        //
        GPIOPinTypeI2CSCL(GPIO_PORTE_BASE, GPIO_PIN_4);
        MAP_GPIOPinTypeI2C(GPIO_PORTE_BASE, GPIO_PIN_5);

        // Configure and Enable the GPIO interrupt. Used for INT signal from the
            // MPU9150
            //
            MAP_GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_2);
            GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_2);
            MAP_GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_FALLING_EDGE);
            MAP_IntEnable(INT_GPIOB);

        // Enable interrupts to the processor.
        //
        MAP_IntMasterEnable();
        // Initialize I2C3 peripheral.
        //
        I2CMInit(&g_sI2CInst, I2C2_BASE, INT_I2C2, 0xff, 0xff,
                     MAP_SysCtlClockGet());


        // Initialize the MPU9150 Driver.
        //
        MPU9150Init(&g_sMPU9150Inst, &g_sI2CInst, MPU9150_I2C_ADDRESS,
                        MPU9150AppCallback, &g_sMPU9150Inst);

        // Wait for transaction to complete
            //
            MPU9150AppI2CWait(__FILE__, __LINE__);

            //
            // Write application specific sensor configuration such as filter settings
            // and sensor range settings.
            //
            g_sMPU9150Inst.pui8Data[0] = MPU9150_CONFIG_DLPF_CFG_94_98;
            g_sMPU9150Inst.pui8Data[1] = MPU9150_GYRO_CONFIG_FS_SEL_250;
            g_sMPU9150Inst.pui8Data[2] = (MPU9150_ACCEL_CONFIG_ACCEL_HPF_5HZ |
                                          MPU9150_ACCEL_CONFIG_AFS_SEL_2G);
            MPU9150Write(&g_sMPU9150Inst, MPU9150_O_CONFIG, g_sMPU9150Inst.pui8Data, 3,
                         MPU9150AppCallback, &g_sMPU9150Inst);

            //
            // Wait for transaction to complete
            //
            MPU9150AppI2CWait(__FILE__, __LINE__);

            //
            // Configure the data ready interrupt pin output of the MPU9150.
            //
            g_sMPU9150Inst.pui8Data[0] = MPU9150_INT_PIN_CFG_INT_LEVEL |
                                            MPU9150_INT_PIN_CFG_INT_RD_CLEAR |
                                            MPU9150_INT_PIN_CFG_LATCH_INT_EN;
            g_sMPU9150Inst.pui8Data[1] = MPU9150_INT_ENABLE_DATA_RDY_EN;
            MPU9150Write(&g_sMPU9150Inst, MPU9150_O_INT_PIN_CFG,
                         g_sMPU9150Inst.pui8Data, 2, MPU9150AppCallback,
                         &g_sMPU9150Inst);

            //
            // Wait for transaction to complete
            //
            MPU9150AppI2CWait(__FILE__, __LINE__);


    }


//*****************************************************************************
//
// Formatting obtained data
//
//*****************************************************************************

void format_data(void){

for(ui32Idx = 0; ui32Idx < 3; ui32Idx++)
                                     {
                                         if (pfData[ui32Idx] < 0)
                                         {
                                             cSign[ui32Idx] = '-';
                                         }
                                         else
                                         {
                                             cSign[ui32Idx] = ' ';
                                         }

                                         //
                                         // Convert float value to a integer truncating the decimal part.
                                         //
                                         i32IPart[ui32Idx] = (int32_t) fabs(pfData[ui32Idx]);

                                         //
                                         // Multiply by 1000 to preserve first three decimal values.
                                         // Truncates at the 3rd decimal place.
                                         //
                                         i32FPart[ui32Idx] = (int32_t) fabs((pfData[ui32Idx] * 1000.0f));

                                         //
                                         // Subtract off the integer part from this newly formed decimal
                                         // part.
                                         //
                                         i32FPart[ui32Idx] = i32FPart[ui32Idx] -
                                                             (i32IPart[ui32Idx] * 1000);

                                         //
                                         // Handle the corner case where a negative number that is less
                                         // than 0.000 was displaying as '-0.000' on the terminal.
                                         //
                                         if ((i32FPart[ui32Idx] == 0) && (i32IPart[ui32Idx] == 0))
                                         {
                                             cSign[ui32Idx] = ' ';
                                         }
                                     }
}
