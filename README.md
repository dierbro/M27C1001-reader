Vintage M27C1001 EPROM reader
===============


**tested on Arduino Due with M27C1001-70XF1 **

    Vcc = 3.3v (Max ratings are -2/7V)
    Vpp = 3.3v or GROUND
    Vss = GROUND
   
   
   PIN 30-46 Address (A0-A16)
   PIN 2-9   Data (Q0-Q7)
   PIN 22    Chip Enable (active when low) (/E)
   PIN 24    Output Enable (active when low) (/G)
   PIN 50    Trigger (Push button)

      $ minicom -D /dev/ttyXXXN -b 115200 -C dump_file
