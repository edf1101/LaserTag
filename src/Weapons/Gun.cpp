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
         bool defaultSuppressed, float volume){
//         ,unsigned char *gunSound


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
//  this->gunSound = gunSound;

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
