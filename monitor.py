import GPUtil, psutil, serial, time


# print(f"{gpu.memoryUsed/1000:.2f}/{gpu.memoryTotal/1000:.2f} GB")
# print(f"USAGE: {gpu.load*100}%")

#cpuTemp, cpuUsage, gpuTemp, gpuUsage, gpuUsedMem, gpuTotalMem, ramUsage, ramUsed, ramTotal
def cpuStatus():
    temp = 99
    usage = f"{psutil.cpu_percent()}"
    return f"{temp},{usage}"

def gpuStatus():
    gpu = GPUtil.getGPUs()[0]
    temp = 99
    usage = f"{gpu.load*100:.0f}"
    usedMem = f"{gpu.memoryUsed/1000:.2f}"
    totalMem = f"{gpu.memoryTotal/1000:.2f}"
    return f"{temp},{usage},{usedMem},{totalMem}"

def ramStatus():
    factor = 9.313225746154785*(10**-10)
    usage = psutil.virtual_memory().percent
    used = f"{psutil.virtual_memory().used*factor:.1f}"
    total = f"{psutil.virtual_memory().total*factor:.1f}"
    return f"{usage},{used},{total}"

while True:
    try:
        arduino = serial.Serial('COM3', 9600)
        while True:
            final_string = f"{cpuStatus()},{gpuStatus()},{ramStatus()}"
            arduino.write(final_string.encode('ascii'))
            print(final_string.encode('ascii'))
            time.sleep(1.5)
        arduino.close()
    except:
        print("No connection")
        time.sleep(2)
        

