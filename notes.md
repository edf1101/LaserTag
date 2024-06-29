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
- Make it scan for I2C devices and use that to choose the screen address.
- Must use a larger program size for ESP32 (I used 'huge APP' partition)
- Have an option to select which 'lobby' to be in. This would be useful for if you have multiple games going on at once. 
This must be sent with the wifi data so commands don't get mixed up and also with the IR data (need to fit in.)
- Add a proper logger instead of Serial.println
- add a name changed bit to playerwrapper so name is changed when gun joins and unum assigned , but doesnt if user already changed name.
- each gamemode should have a player struct for starting player data. On gamemode reset all network players are reset to this data.
- Player struct should have a static func to set its player struct to a starting player struct(in gamemode).
- When a gamemode is set the laser tagger should reset its player data to the starting player data using the static player func above.
- Games should have a function to return if they are rejoinable or not.
- Game should have a function to return important game info to be sent over wifi for a rejoining player
and a function to set the game info from the wifi data.
- When becoming admin, the player should send out an am I admin packet to all other players. Wait 1s to see if any responses
if not do usual thing. If so then do the join game as existing routine.
- 

## Plan
- Have player kill confirm work
- make an constantly maintained active nodes vector.
- create leaderboard menu
- implement rest of commands
- add it so commands can be sent as BROADCAST, IR, MYSELF. be able to set that mode in menu and update command menus accordingly.
- add teams
- add team DM game
- add a logger
- Can only join if gun default guns are same.
- design latch circuit
- build enclosure / pcbs
- anticheat system

## Potential issues if recreating
- The 128x64 OLED screen sometimes has different addresses / pin layouts be aware of pin layouts if using this PCB

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
