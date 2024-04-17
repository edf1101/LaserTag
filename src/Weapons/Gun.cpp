/*
 * Created by Ed Fillingham on 10/04/2024.
 *
 * This class represents a basic gun object.
*/

#include "Gun.h"

using namespace Weapons; // So we don't have to prefix everything with Gun::


Gun::Gun(int gunId, std::string gunName, std::string gunAcronym,
         Images::ImageData _gunImage,
         int magSize, int magStartCount, int magReloadTime, ReloadType magReloadType,
         int damage, int fireRateNormal, int fireRateFast, int fireRateSlow, int shotsPerBurst,
         bool defaultSuppressed, float volume,
         XT_Wav_Class *gunSound) {


  // Move over the default characteristics from the constructor to the class variables
  this->gunID = gunId;
  this->gunName = std::move(gunName);
  this->gunAcronym = std::move(gunAcronym);
  this->gunImage = _gunImage;
  this->magSize = magSize;
  this->magStartCount = magStartCount;
  this->magReloadTime = magReloadTime;
  this->magReloadType = magReloadType;
  this->damage = damage;
  this->fireRateNormal = fireRateNormal;
  this->fireRateFast = fireRateFast;
  this->fireRateSlow = fireRateSlow;
  this->shotsPerBurst = shotsPerBurst;
  this->defaultSuppressed = defaultSuppressed;
  this->volume = volume;
  this->gunSound = gunSound;

  // Set the reload description based on the reload type
  if (magReloadType == ReloadType::PRESS_PER_BULLET) {
    this->reloadDescription = "Press x" + std::to_string(magSize);
  } else if (magReloadType == ReloadType::PRESS_FOR_ALL) {
    this->reloadDescription = "Press 2x";
  } else if (magReloadType == ReloadType::AUTO) {
    this->reloadDescription = "Automatic";
  }

  resetCharacteristics();
}

void Gun::resetCharacteristics() {
  // Set the gun instance variables
  this->magsRemaining = magStartCount;
  this->bulletsInMag = magSize;
  this->reloading = false;
  this->reloadCount = 0;
  this->fireRate = fireRateNormal;
  this->burstCount = 0;
  this->suppressed = defaultSuppressed;
}

int Gun::getIndex() const {
  // Return the gun's index
  return gunID;
}

bool Gun::tryFire() {

  // Before we check if its reloading, check if it's a PRESS_PER_BULLET gun and
  // it has reloaded >0 bullets. Done here as this is called when a trigger is pressed.
  if (reloading && magReloadType == ReloadType::PRESS_PER_BULLET && reloadCount > 0) {
    reloading = false;
    bulletsInMag = reloadCount;
    reloadCount = 0;
  }

  if (reloading) {
    return false; // If the gun is reloading, it can't fire
  }

  if (bulletsInMag == 0 && magsRemaining == 0) {
    return false; // no bullets in gun and no refill mags can't fire
  }

  if (millis() - lastFired < fireRate) {
    return false; // If the gun has fired too recently, it can't fire
  }

  if (burstCount >= shotsPerBurst && shotsPerBurst != -1) {
    return false; // If the gun has fired too many shots in the current burst, it can't fire
  }


  // It passed the tests so fire the gun
  lastFired = millis();
  burstCount++;

  // bullet decrement logic
  bulletsInMag--;

  if (bulletsInMag == 0 && magsRemaining > 0) { // if mag is empty & we have more mags start reload
    magsRemaining--;
    reloading = true;
    reloadStartTime = millis();
    drawHUD();
  }


  return true; // This means that the gun can fire and just has
}

void Gun::resetBurstCount() {
  // Reset the burst count (when trigger released)
  burstCount = 0;
}

bool Gun::getSuppressed() {
  // Return the suppressed state of the gun
  return suppressed;
}

void Gun::setSuppressed(bool _suppressed) {
  // Set the suppressed state of the gun
  suppressed = _suppressed;
}

void Gun::reloadLoop() {
  // This function is called everytime Firing loop runs to sort reloading logic

  if (!reloading) { // If not reloading then ignore this function
    return;
  }

  // If it's an AUTO reload gun & the reload time has passed then stop reload
  if (magReloadType == ReloadType::AUTO &&
      millis() - reloadStartTime > magReloadTime) {
    reloading = false;
    bulletsInMag = magSize;
  }
    // If it's A PRESS_FOR_ALL gun and enough presses have been made
  else if (magReloadType == ReloadType::PRESS_FOR_ALL &&
           reloadCount == PRESSES_TO_RELOAD) {
    reloading = false;
    bulletsInMag = magSize;
    reloadCount = 0;
  } else if (magReloadType == ReloadType::PRESS_PER_BULLET &&
             reloadCount == magSize) {

    reloading = false;
    bulletsInMag = magSize;
    reloadCount = 0;
  }
  drawHUD();

  // If it's a PRESS_PER_BULLET gun and the trigger is pressed we deal with it in the Fire() function
}

void Gun::reloadAddBullet() {
  // This function is called when a bullet is added to the gun
  // (triggered by magazine button down)

  if (!reloading) { // If not reloading then ignore this function
    return;
  }
  reloadCount++;
  bulletsInMag = reloadCount;
  drawHUD();

  reloadLoop(); // This disables reloading if the gun is done reloading
}

void Gun::setFireRate(FireRate _fireRate) {
  // Set the fire rate of the gun according to the FireRate enum

  if (_fireRate == FireRate::NORMAL) {
    fireRate = fireRateNormal;
  } else if (_fireRate == FireRate::FAST) {
    fireRate = fireRateFast;
  } else if (_fireRate == FireRate::SLOW) {
    fireRate = fireRateSlow;
  }
}

int Gun::createHash() {
  // Create a hash of the gun's characteristics
  int hash = 0;
  hash += magSize;
  hash += magStartCount;
  hash += magReloadTime;
  hash += damage;
  hash += fireRateNormal;
  hash += fireRateFast;
  hash += fireRateSlow;
  hash += shotsPerBurst;
  hash += defaultSuppressed;
  hash += volume;
  return hash;
}

std::string Gun::getName() {
  // Return the gun's name
  return gunName;
}

XT_Wav_Class *Gun::getSound() {
  // Return the gun's sound
  return gunSound;
}

int Gun::getDamage() {
  // Return the gun's damage
  return damage;
}

int Gun::getAmmoRemaining() {
  // Returns ammo remaining for the gun
  return bulletsInMag;
}

int Gun::getMagsRemaining() {
  // Returns mags remaining for the gun
  return magsRemaining;
}

std::string Gun::getAcronym() {
  // Returns guns acronym
  return gunAcronym;
}

void Gun::setHUDFunction(std::function<void(void)> _drawHUD) {
  // Set the function to draw the gun's HUD
  drawHUD = _drawHUD;
}

std::string Gun::getReloadDescription() {
    // Get the description of how the gun reloads
  return reloadDescription;
}

bool Gun::getReloading() {
  // Get whether the gun is currently reloading
  return reloading;
}
