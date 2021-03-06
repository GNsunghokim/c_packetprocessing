/*
 * Copyright (C) 2012-2015,  Netronome Systems, Inc.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file          lib/net/eth.h
 * @brief         Definitions for Ethernet header parsing
 *
 * Incomplete, new definitions will be added as/when needed
 */

#ifndef _NET_ETH_H_
#define _NET_ETH_H_

/**
 * Header length definitions
 * @NET_ETH_ALEN           Length of Ethernet MAC address
 * @NET_8021Q_LEN          Length of a VLAN tag
 * @NET_ETH_LEN            Length of a Ethernet header, no VLAN
 * @NET_ETH_8021Q_LEN      Length of a Ethernet header, with VLAN
 * @NET_ETH_FCS_LEN        Length of Ethernet FCS
 */
#define NET_ETH_ALEN            6
#define NET_8021Q_LEN           4
#define NET_ETH_LEN             14
#define NET_ETH_8021Q_LEN       (NET_ETH_LEN + NET_8021Q_LEN)
#define NET_ETH_FCS_LEN         4


/**
 * An incomplete list of Ethernet protocol types
 * See: http://en.wikipedia.org/wiki/EtherType
 */
#define NET_ETH_TYPE_IPV4       0x0800  /** Internet Protocol, Version 4 */
#define NET_ETH_TYPE_ARP        0x0806  /** Address Resolution Protocol (ARP) */
#define NET_ETH_TYPE_WOL        0x0842  /** Wake-on-LAN Magic Packet  */
#define NET_ETH_TYPE_TRILL      0x22f3  /** IETF TRILL Protocol */
#define NET_ETH_TYPE_TEB        0x6558  /** Trans Ether Bridging */
#define NET_ETH_TYPE_RARP       0x8035  /** Reverse Address Resolution */
#define NET_ETH_TYPE_TPID       0x8100  /** VLAN-tagged frame (IEEE 802.1Q) */
#define NET_ETH_TYPE_IPV6       0x86dd  /** Internet Protocol, Version 6 */
#define NET_ETH_TYPE_MPLS       0x8847  /** MPLS unicast */
#define NET_ETH_TYPE_MPLS_MC    0x8848  /** MPLS multicast */
#define NET_ETH_TYPE_JUMBO      0x8870  /** Jumbo Frames */
#define NET_ETH_TYPE_LOOPBACK   0x9000  /** Configuration Test Protocol  */
#define NET_ETH_TYPE_QINQ       0x9100  /** Q-in-Q IEEE 802.1ad */

/**
 * Ethernet address macros
 */
#define NET_ETH_LADMIN_ADDR     0x02    /** Locally assigned address. */
#define NET_ETH_GROUP_ADDR      0x01    /** Multicast or broadcast address. */


/**
 * VLAN definitions.
 *
 * @NET_ETH_TCI_PCP_of          Priority
 * @NET_ETH_TCI_CFI_MASK        Canonical Format Indicator
 * @NET_ETH_TCI_VLAN_PRESENT    Appropriate the CFI for VLAN indication
 * @NET_ETH_TCI_VID_of          VLAN ID
 */
#define NET_ETH_TCI_PCP_of(_x)          (((_x) >> 13) & 0x3)
#define NET_ETH_TCI_CFI_MASK            0x1000
#define NET_ETH_TCI_VLAN_PRESENT        (NET_ETH_TCI_CFI_MASK)
#define NET_ETH_TCI_VID_of(_x)          ((_x) & 0x0fff)


#if defined(__NFP_LANG_MICROC)

#include <nfp.h>
#include <stdint.h>

/**
 * Ethernet header structure
 */
__packed struct eth_addr {
    uint8_t  a[NET_ETH_ALEN];
};

__packed struct eth_hdr {
    struct eth_addr dst;                /** Destination address */
    struct eth_addr src;                /** Source address */
    uint16_t type;                      /** Protocol type */
};

/**
 * VLAN header
 */
__packed struct vlan_hdr {
    uint16_t tci;                       /** Tag control identifier */
    uint16_t type;                      /** Protocol type */
};

/**
 * Ethernet + VLAN header structure
 */
__packed struct eth_vlan_hdr {
    struct eth_addr dst;                /** Destination address */
    struct eth_addr src;                /** Source address */
    uint16_t tpid;                      /** Tag protocol identifier */
    uint16_t tci;                       /** Tag control identifier */
    uint16_t type;                      /** Protocol type */
};


/*
 * Utility functions/macros
 */

/**
 * Check if a Ethernet address is a unicast address.
 */
#define NET_ETH_IS_UC_ADDR(_a) \
    ((((struct eth_addr *)_a)->a[0] & NET_ETH_GROUP_ADDR) == 0)

/**
 * Check if a Ethernet address is a broadcast address.
 */
#define NET_ETH_IS_BC_ADDR(_a) \
    (((uint16_t *)_a)[0] == 0xFFFF && \
     ((uint16_t *)_a)[1] == 0xFFFF && \
     ((uint16_t *)_a)[2] == 0xFFFF)

/**
 * Check if a Ethernet address is a multicast address.
 */
#define NET_ETH_IS_MC_ADDR(_a) \
    (((struct eth_addr *)_a)->a[0] & NET_ETH_GROUP_ADDR)

#endif /* MicroC code */

#endif /* _NET_ETH_H_ */

/* -*-  Mode:C; c-basic-offset:4; tab-width:4 -*- */
