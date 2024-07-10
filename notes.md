# Notes & Ideas

## Notes

- To list serial ports on windows:
```Get-CimInstance -Class Win32_SerialPort | Select-Object Name, Description, DeviceID```
- To list on mac ```dmesg | grep tty   ```

## Ideas
- Have a define to turn on or off Serial debug
- Anticheat could work by making a hash of all the weapons and checking if each gun has the same total weapon hash.
- Same with test mode except it could be hold down trigger on start instead of define.
- Latch circuit to turn on the gun and timer / menu to turn off the gun
- modifying techcamp code to run on this hardware, and having the leaderboard display on the side screen would be pretty cool.
Would also involve removing their LEDs and replacing with our WS2182B LEDs.
- Admin have the option to lower all volumes (dont do individual volumes as would be unfair to be stealthy), admin can also disable LEDs
- Users should be able to enable or disable vibration motors.
- Have a mode where all the shooting effects are laser sounds so it doesn't sound like real guns.
- Have a PC Interface that communicates with a "base node" via HTTP or serial that can run some python code to display stats, run commands etc.
If web interface uses flask then other phones etc can access it. send JSON over serial for ease of use.
- can have a shot accuracy stat
- Sort out the canTakeDamage / need admin fields of menus
- make things more staticy where poss
- Could install all libs in the src code so that it can be run on any computer without needing to install anything.
- Add a proper logger instead of Serial.println
- When becoming admin, the player should send out an am I admin packet to all other players. Wait 1s to see if any responses
if not do usual thing. If so then do the join game as existing routine.
- logger have diff levels of logging
- admin can turn down IR and volume

## Plan
- implement rest of commands apart from guns
- add it so commands can be sent as BROADCAST, IR, MYSELF. be able to set that mode in menu and update command menus accordingly.
- Gun groups 
- add teams (and auto team balancing) 
- add team DM game
- add a logger (debug screen messages from here)
- player can turn on and off vibration motors
- admin can enable/disable/change: volume, LEDs, IR
- design latch circuit
- build enclosure / pcbs
- PC serial stats interface in python

## Potential issues if recreating
- The 128x64 OLED screen sometimes has different addresses / pin layouts be aware of pin layouts if using this PCB
- Must use a larger program size for ESP32 (I used 'huge APP' partition)

## Tests
- Try changing the gun group while a player is viewing a gun in choice menu that that has been disallowed

## Commands
### Game modifications
- pause
- play
- Stop


### Player modifications
- Add a life
- Remove a life
- 0 lives
- Inf mags on
- Inf mags off
- Inf ammo on
- Inf ammo off
- Inf Liveson
- Inf Lives off
- Invincible on 
- Invincible off
- Suppressor on
- Suppressor off
- Fast fire
- slow fire
- normal fire
- Fake kill confirm
