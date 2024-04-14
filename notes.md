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
- Implement fireing where it checks player is able to fire and gamemode state is allowed to fire
- different kind of leaderboards for different games. Inheritance?