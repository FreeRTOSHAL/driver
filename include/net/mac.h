/* SPDX-License-Identifier: MIT */
/*
 * Author: Andreas Werner <kernel@andy89.org>
 * Date: 2016
 */
#ifndef ETHNERMAC_H_
#define ETHNERMAC_H_
#include <FreeRTOS.h>
#include <list.h>
#include <stdint.h>
#include <stdbool.h>
#include <system.h>
#include <semphr.h>
#include <hal.h>
#include <net/net.h>
struct mac;

#ifdef CONFIG_MAC_MULTI
/**
 * Function of a driver in Multi Driver implementation mode 
 */
struct mac_ops {
};
#endif
enum mac_type {
	MAC_ETHERNET,
};
enum mac_status {
	MAC_DOWN,
	MAC_UP,
	MAC_SERACHING,
};
struct mac_generic {
	/**
	 * true = is init
	 * false = is not init
	 */
	bool init;
#ifdef CONFIG_INSTANCE_NAME
	/**
	 * Name of Driver Instance for Debugging 
	 */
	const char *name;
#endif
	/**
	 * Mutex
	 */
	OS_DEFINE_MUTEX_RECURSIVE(lock);
#ifdef CONFIG_MAC_MULTI
	/**
	 * Ops of driver in Multi mode
	 */
	const struct mac_ops *ops;
#endif
	enum mac_type type;
	enum mac_status status;
	struct net *net;
	struct phy *phy;
	struct phy **phys;
	uint8_t len;
};
inline enum mac_type mac_getType(struct mac *mac) {
	struct mac_generic *gen = (struct mac_generic *) mac;
	return gen->type;
}
inline enum mac_type mac_getStatus(struct mac *mac) {
	struct mac_generic *gen = (struct mac_generic *) mac;
	return gen->status;
}
inline int32_t mac_setNet(struct mac *mac, struct net *net) {
	struct mac_generic *gen = (struct mac_generic *) mac;
	gen->net = net;
	return 0;
}
inline struct net *mac_getNet(struct mac *mac) {
	struct mac_generic *gen = (struct mac_generic *) mac;
	return gen->net;
}
inline int32_t mac_setPhy(struct mac *mac, struct phy *phy) {
	struct mac_generic *gen = (struct mac_generic *) mac;
	gen->phy = phy;
	return 0;
}
inline struct phy *mac_getPhy(struct mac *mac) {
	struct mac_generic *gen = (struct mac_generic *) mac;
	return gen->phy;
}
inline int32_t mac_setPhys(struct mac *mac, struct phy **phys, uint8_t len) {
	struct mac_generic *gen = (struct mac_generic *) mac;
	gen->phys = phys;
	gen->len = len;
	return 0;
}
inline struct phy **mac_getPhys(struct mac *mac, uint8_t *len) {
	struct mac_generic *gen = (struct mac_generic *) mac;
	*len = gen->len;
	return gen->phys;
}
#ifndef CONFIG_MAC_MULTI
/**
 * Init Function
 * \param index in macs Array
 * \return Net Instants or NULL
 */
struct mac *mac_init(uint32_t index);
/**
 * Deinit Driver Instants 
 * \param mac Instant
 * \return 0 on ok -1 on failure
 */
int32_t mac_deinit(struct mac *mac);
int32_t mac_mdioRead(struct mac *mac, uint8_t id, uint8_t addr, uint16_t *value);
int32_t mac_mdioWrite(struct mac *mac, uint8_t id, uint8_t addr, uint16_t value);
int32_t mac_send(struct mac *mac, struct netbuff *buff);
int32_t mac_enable(struct mac *mac);
int32_t mac_disable(struct mac *mac);
int32_t mac_setMacAddress(struct mac *mac, uint8_t *address);
int32_t mac_getMacAddress(struct mac *mac, uint8_t *address);
int32_t mac_getMTU(struct mac *mac);
void mac_adjust_link(struct mac *mac);
int32_t mac_connect(struct mac *mac, struct phy *phy, struct net *net);
#else
# error TODO not implement
#endif
#endif
