# Notes & Ideas

## Notes

- To list serial ports on windows:
```Get-CimInstance -Class Win32_SerialPort | Select-Object Name, Description, DeviceID```
- To list on mac ```dmesg | grep tty   ```

## Ideas
- Anticheat (If everyone doesn't have a certain weapon then it can't be used)
- System to check no overlapping unitnums, else it will be modified.
- FastLED stuff
- Optional Vibration motors
- Have a define to turn on or off Serial debug
- Anticheat could work by making a hash of all the weapons and checking if each gun has the same total weapon hash.
- Would be nice if beacon code was in this same repository and you just changed a define 
at the top of the file to switch between the two.
- Same with test mode except it could be hold down trigger on start instead of define.
- Latch circuit to turn on the gun and timer / menu to turn off the gun
- Bump the bottom of the gun twice to reload magazine.
- Have gun groups so you can have a game of only pistols, only default guns etc.
- Have a gun game mode eg COD
- manhunt mode
- tag / bomb mode
- different kind of leaderboards for different games. Inheritance?
- Need a canTakeDamage() similar to canFire()
- also can probs simplfy the canFire() function to just have a canfire in Lasertag that contains all the individual parts
- modifying techcamp code to run on this hardware, and having the leaderboard display on the side screen would be pretty cool.
Would also involve removing their LEDs and replacing with our WS2182B LEDs.
- Admin have the option to lower all volumes (dont do individual volumes as would be unfair to be stealthy), admin can also disable LEDs
- Admin can also disable the gun from firing (kick from game ish)
- Users should be able to enable or disable vibration motors.