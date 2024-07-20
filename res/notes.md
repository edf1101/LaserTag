# Notes & Ideas

## Notes

- To list serial ports on windows:
```Get-CimInstance -Class Win32_SerialPort | Select-Object Name, Description, DeviceID```
- To list on mac ```dmesg | grep tty   ```

## Ideas
- Admin have the option to lower all volumes (dont do individual volumes as would be unfair to be stealthy), admin can also disable LEDs
- Users should be able to enable or disable vibration motors.
- Have a mode where all the shooting effects are laser sounds so it doesn't sound like real guns.
- make things more staticy where poss
- When becoming admin, the player should send out an am I admin packet to all other players. Wait 1s to see if any responses
if not do usual thing. If so then do the join game as existing routine.
- admin can turn down IR and volume
- Other menu in admin base menu is to autoteam balance.(or maybe in teams menu have an autobalance 2 team,3 team, 4 team etc)

## Plan
- Have a python script to make all folders in /Libs vendored
- add teams (and auto team balancing) 
- add team DM game
- player can turn on and off vibration motors
- admin can enable/disable/change: volume, LEDs, IR, gun or laser sounds
- Improve the sound effects
- bundle up the software (move all libs to /Libs)

## Potential issues if recreating
- The 128x64 OLED screen sometimes has different pin layouts be aware of pin layouts if using this PCB
- Must use a larger program size for ESP32 (I used 'huge APP' partition)
