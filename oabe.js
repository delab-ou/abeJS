///
/// Copyright (c) 2018 Zeutro, LLC. All rights reserved.
///
/// This file is part of Zeutro's OpenABE.
///
/// OpenABE is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Affero General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// OpenABE is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU Affero General Public License for more details.
///
/// You should have received a copy of the GNU Affero General Public
/// License along with OpenABE. If not, see <http://www.gnu.org/licenses/>.
///
/// You can be released from the requirements of the GNU Affero General
/// Public License and obtain additional features by purchasing a
/// commercial license. Buying such a license is mandatory if you
/// engage in commercial activities involving OpenABE that do not
/// comply with the open source requirements of the GNU Affero General
/// Public License. For more information on commerical licenses,
/// visit <http://www.zeutro.com>.
///
/// \brief  Example use of the Keystore + OpenABE API with KP-ABE
///

#include <iostream>
#include <string>
#include <cassert>
#include <map>
#include <vector>
#include <openabe/openabe.h>
#include <openabe/zsymcrypto.h>
#define BUFFER 32

using namespace std;
using namespace oabe;
using namespace oabe::crypto;

int main(int argc, char **argv) {

  InitializeOpenABE();

  cout << "Testing CP-ABE context" << endl;

  // instantiate a crypto box CP-ABE context
  OpenABECryptoContext cpabe("CP-ABE");

  char str1[BUFFER],str2[BUFFER];

  string ptext = "", ctext, dtext;

  cout << "Please input string" << endl;
  cin.getline(str1, BUFFER, '\n');
  ptext = str1;

  cpabe.generateParams();

  cout << "Please input your attribute" << endl;
  cin.getline(str2, BUFFER, '\n');

  cpabe.keygen("|attr1|attr2|", "key0");

  cpabe.encrypt("attr1 and attr2", ptext, ctext);
  cout << "ciphered text: " << ctext << endl;

  bool result = cpabe.decrypt("key0", ctext, dtext);
  assert(result && ptext == dtext);
  cout << "decrypted text: " << dtext << endl;

  oabe::ShutdownOpenABE();

  return 0;
}
