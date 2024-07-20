# Notes & Ideas

## Notes

- To list serial ports on windows:
```Get-CimInstance -Class Win32_SerialPort | Select-Object Name, Description, DeviceID```
- To list on mac ```dmesg | grep tty   ```

## Ideas
- Have a define to turn on or off Serial debug
- Same with test mode except it could be hold down trigger on start instead of define.
- Latch circuit to turn on the gun and timer / menu to turn off the gun
- Admin have the option to lower all volumes (dont do individual volumes as would be unfair to be stealthy), admin can also disable LEDs
- Users should be able to enable or disable vibration motors.
- Have a mode where all the shooting effects are laser sounds so it doesn't sound like real guns.
- Have a PC Interface that communicates with a "base node" via HTTP or serial that can run some python code to display stats, run commands etc.
If web interface uses flask then other phones etc can access it. send JSON over serial for ease of use. can have a shot accuracy stat
- make things more staticy where poss
- Could install all libs in the src code so that it can be run on any computer without needing to install anything.
- When becoming admin, the player should send out an am I admin packet to all other players. Wait 1s to see if any responses
if not do usual thing. If so then do the join game as existing routine.
- admin can turn down IR and volume
- Other menu in admin base menu is to autoteam balance.(or maybe in teams menu have an autobalance 2 team,3 team, 4 team etc)

## Plan
- add teams (and auto team balancing) 
- add team DM game
- player can turn on and off vibration motors
- admin can enable/disable/change: volume, LEDs, IR, gun or laser sounds
- PC serial stats interface in python

## Potential issues if recreating
- The 128x64 OLED screen sometimes has different pin layouts be aware of pin layouts if using this PCB
- Must use a larger program size for ESP32 (I used 'huge APP' partition)
