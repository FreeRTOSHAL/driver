/* SPDX-License-Identifier: MIT */
/*
 * Author: Andreas Werner <kernel@andy89.org>
 * Date: 2016
 */
#ifndef NLIBC_STUB_H_
#define NLIBC_STUB_H_
#include <uart.h>
#include <stdint.h>
/**
 * \defgroup Newlib Newlib Function
 * \ingroup HAL
 * \code
 * #include <nlibc_stub.h>
 * \endcode
 * 
 * Newlib Function
 * \{
 */
/**
 * Init Newlib
 * \param std_in UART instance for Standard In 
 * \param std_out UART instance for Standard Out
 * \return -1 on error 0 on ok
 */
int32_t nlibc_init(struct uart *std_in, struct uart *std_out);
/**\}*/
#endif
