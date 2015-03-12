# Introduction #

---

_Software Development Environment Setup_
Update the status of your computer for an efficient season.
**DO NOT IN ANY WAY CHECK A BOX WITHOUT FIRST ACTUALLY TESTING. JUST BECAUSE YOU INSTALLED SOMETHING DOES NOT MEAN IT IS OPERATIONAL AND YOU MUST TEST IT IN ORDER TO CHECK IT  ON THE BELOW CHART**


# Details #
## PASSES TEST ##
A computer "passes test" when it can do following:
  * "FIRST" menu appears in Windriver
  * Can create FRC simple robot project
  * Can Compile without errors
  * Can download to robot
  * Can debug

## 2CAN ##
At the 2CAN [website](http://crosstheroadelectronics.com/2CAN.htm) download the following:
  * indowsUtility.zip         -->Install it
  * rcmanual.pdf
  * irmware.crf               -->Probably don't use... i think we use different firmware
  * rcfrimwareplugin.zip      -->This has OUR **.crf file.**

**DON'T UPDATE THE CHART THING BELOW UNTIL YOU CAN COMUNNICATE WITH JAGUARS...**

## Source Control ##
  1. Connect to 1073-sw network
  1. Browse to source code server (S Dell) (IP hidden given the unrestricted access to this site) and confirm one can see code
  1. Install tortoiseHG and/or Mercurial Eclipse
  1. Create clone from source code machine in your windriver workspace folder
  1. Import project into windriver (don't copy files, leave them where they are)
  1. If you already have clone, then just pull and update from source code server
  1. Code and test
  1. Commit changes (to your own local clone)
  1. Pull and Update and Merge before final delivery into your own local clone
  1. Re-build and test again and manually inspect merge results
  1. Commit any changes resulting from merge into your local clone
  1. Push your clone changes to the source server (S Dell)


## Chart ##

| **Computer** | **Owner** | **Windriver** | **NI** | **Updates** | **Driverstation** | [Tortoise Hg](http://tortoisehg.bitbucket.org/download/index.html) | [Eclipse Hg](http://javaforge.com/project/HGE) | **PASSED TEST** | [2CAN Stuff](http://crosstheroadelectronics.com/2CAN.htm) | **Source Control** |
|:-------------|:----------|:--------------|:-------|:------------|:------------------|:-------------------------------------------------------------------|:-----------------------------------------------|:----------------|:----------------------------------------------------------|:-------------------|
| 1  | Lasya      | X | X | X | X | X |   |   |   |   |
| 2  | Evin       | X   | X | X | X | X | X | X |  X | X  |
| 3  | Ryan       |   |   |   |   |   |   |   |   | X |
| 4  | S HP Ansel |   |   |   |   |   |   |   | X |   |
| 5  | S Dell     |   |   |   |   |   |   |   |   | **SERVER**  |
| 6  | Heden      |   |   |   |   |   |   |   |   |  |
| 7  | DH HDX     |   |   |   |   |   |   |   |   |   |
| 8  | DG Dell    |   |   |   |   |   |   |   |   |   |
| 9  | Ben        | Q | Q | Q | Q | Q | Q | Q |  NO | Q |
| 10 | Will   | X | X | X | X | X |   |   |   |   |
| 11 | Kate       | X | X | X | X | X | X | X |   | X |
| 12 | Miguel     | X | X | X | X | X |   |   |   |   |
| 13 | KC         | X | X | X | X | X | X | X |   | X |