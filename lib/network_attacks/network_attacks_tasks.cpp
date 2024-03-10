/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or
 * https://capibarazero.github.io/). Copyright (c) 2024 Andrea Canale.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "network_attacks.hpp"

void dhcp_starvation_task(void *pv) {
  NetworkAttacks *params = static_cast<NetworkAttacks *>(pv);
  params->dhcp_starvation();
}

void evilportal_task(void *pv) {
  NetworkAttacks *params = static_cast<NetworkAttacks *>(pv);
  params->start_evilportal();
}