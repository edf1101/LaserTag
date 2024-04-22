# Notes & Ideas

## Notes

- To list serial ports on windows:
```Get-CimInstance -Class Win32_SerialPort | Select-Object Name, Description, DeviceID```
- To list on mac ```dmesg | grep tty   ```

## Ideas
- Anticheat (If everyone doesn't have a certain weapon then it can't be used)
- System to check no overlapping unitnums, else it will be modified.
- Have a define to turn on or off Serial debug
- Anticheat could work by making a hash of all the weapons and checking if each gun has the same total weapon hash.
- Would be nice if beacon code was in this same repository and you just changed a define 
at the top of the file to switch between the two.
- Same with test mode except it could be hold down trigger on start instead of define.
- Latch circuit to turn on the gun and timer / menu to turn off the gun
- Have gun groups so you can have a game of only pistols, only default guns etc.
- Have a gun game mode eg COD
- manhunt mode
- tag / bomb mode
- different kind of leaderboards for different games. Inheritance?
- modifying techcamp code to run on this hardware, and having the leaderboard display on the side screen would be pretty cool.
Would also involve removing their LEDs and replacing with our WS2182B LEDs.
- Admin have the option to lower all volumes (dont do individual volumes as would be unfair to be stealthy), admin can also disable LEDs
- Admin can also disable the gun from firing (kick from game ish)
- Users should be able to enable or disable vibration motors.
- Shooting sound should be after IR sent so that it doesn't draw away power from the IR LED.
- unitnum mac address system to prevent overlapping unitnums
- flag with a keypad would be cool for if doing bomb defusal game
- up to 2^7(128) players possible and 2^4 weapons (16). Teams are done over wifi so should be as many as wanted.
- unitnum / mac address system can be stored in player class
- Have a mode where all the shooting effects are laser sounds so it doesn't sound like real guns.
- For creating name have an option to select recently used names. (store recently used names in eeprom and have an algorithm
to reduce writes eg. have 5 addresses for last used names and a pointer for which is most recently used so dont have to update all)
- update screen when mag reloaded
- menu selector should have a field for requires admin to enter.
- Make reload message pop up on info widget.
- player struct that holds stats and the current Player class becomes a wrapper. That way when we have the wifi player data
its more reusable
- Have a PC Interface that communicates with a "base node" via HTTP or serial that can run some python code to display stats, run commands etc.
If web interface uses flask then other phones etc can access it.
- Investigate connecting to guns via wifi / bluetooth to change settings.
- Grenade???
- For LEDs have a stack ish system so it doesn't overwrite long effects if it was doing a quick fire effect or something.
- Sort out the canTakeDamage / need admin fields of menus
- make things more staticy where poss
- Could install all libs in the src code so that it can be run on any computer without needing to install anything.

## Plan
- create name selector menu / admin password menu (should be same class ish)
- create wifi player management system. (includes unitnum clash detection)
- create leaderboard menu
- create command system / menu
- add team DM game
- design latch circuit
- build enclosure / pcbs
- Test mode for guns
- anticheat system
- Add new gun game gamemode
- create flag / respawn point (pcb code & enclosure)
- create capture flag game
- create domination game
- create bomb defusal game
- Add new manhunt gamemode
- Add new tag gamemode
- modify techcamp code to run on this hardware

## Tests
- Try changing the gun group while a player is viewing a gun in choice menu that that has been disallowed