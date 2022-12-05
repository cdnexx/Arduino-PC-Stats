import psutil
import time
import GPUtil
from colors import colors

def display_usage(cpu_usage, mem_usage, bars=50):
    cpu_percent = cpu_usage/100.0
    cpu_bar = '█' * int(cpu_percent*bars) + '-' * (bars-int(cpu_percent*bars))
    mem_percent = mem_usage/100.0
    mem_bar = '█' * int(mem_percent*bars) + '-' * (bars-int(mem_percent*bars))

    print(f"\r{colors.txt.purple}CPU: |{cpu_bar}| {cpu_usage:.2f}%  ", end=colors.reset)
    print(f"{colors.txt.red}RAM: |{mem_bar}| {mem_usage:.2f}%  ", end=f"\r{colors.reset}")
    
while True:
    display_usage(psutil.cpu_percent(), psutil.virtual_memory().percent, 30)
    # display_usage(GPUtil.getGPUs()[0].load*100,GPUtil.getGPUs()[0].load*100)
    time.sleep(0.5)