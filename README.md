# my_bash

## проблема незакрытых дескрипторов
    проверка:
    ```C

    1) ps aux 
    2) ps -p<PID>
    3)ls -l /proc/<PID>/fd
    
    ``` 

### до исправления:
    <img src="./readme_src/fd_list.png" width="800"/>

### после:
    <img src="./readme_src/fd_list_1.png" width="800"/>
