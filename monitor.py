import GPUtil, psutil, serial, time, clr
clr.AddReference(r'C:/Users/franc/Downloads/openhardwaremonitor-v0.9.6/OpenHardwareMonitor/OpenHardwareMonitorLib')
from OpenHardwareMonitor.Hardware import Computer


# print(f"{gpu.memoryUsed/1000:.2f}/{gpu.memoryTotal/1000:.2f} GB")
# print(f"USAGE: {gpu.load*100}%")

#cpuTemp, cpuUsage, gpuTemp, gpuUsage, gpuUsedMem, gpuTotalMem, ramUsage, ramUsed, ramTotal
def cpuStatus():
    temp = 99
    usage = f"{psutil.cpu_percent():.0f}"
    return f"{temp},{usage}"

def gpuStatus():
    gpu = GPUtil.getGPUs()[0]
    temp = gpuTemp()
    usage = f"{gpu.load*100:.0f}"
    usedMem = f"{gpu.memoryUsed/1000:.2f}"
    totalMem = f"{gpu.memoryTotal/1000:.2f}"
    return f"{temp},{usage},{usedMem},{totalMem}"

def gpuTemp():
    c = Computer()
    c.CPUEnabled = True # get the Info about CPU
    c.GPUEnabled = True # get the Info about GPU
    c.Open()
    for a in range(0, len(c.Hardware[1].Sensors)):
        # print(c.Hardware[0].Sensors[a].Identifier)
        if "/temperature" in str(c.Hardware[1].Sensors[a].Identifier):
            temp = f"{int(c.Hardware[1].Sensors[a].get_Value())}"
            return temp
            # c.Hardware[1].Update()

def ramStatus():
    factor = 9.313225746154785*(10**-10)
    usage = f"{psutil.virtual_memory().percent:.0f}"
    used = f"{psutil.virtual_memory().used*factor:.1f}"
    total = f"{psutil.virtual_memory().total*factor:.1f}"
    return f"{usage},{used},{total}"

while True:
    try:
        arduino = serial.Serial('COM3', 9600)
        while True:
            final_string = f"{cpuStatus()},{gpuStatus()},{ramStatus()}"
            arduino.write(final_string.encode('ascii'))
            # print(final_string.encode('ascii'))
            time.sleep(0.2)
        arduino.close()
    except:
        print("No connection")
        time.sleep(2)
        