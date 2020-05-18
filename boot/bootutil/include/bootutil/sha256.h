/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (c) 2017-2019 Linaro LTD
 * Copyright (c) 2017-2019 JUUL Labs
 */

/*
 * This module provides a thin abstraction over some of the crypto
 * primitives to make it easier to swap out the used crypto library.
 *
 * At this point, there are two choices: MCUBOOT_USE_MBED_TLS, or
 * MCUBOOT_USE_TINYCRYPT.  It is a compile error there is not exactly
 * one of these defined.
 */

#ifndef __BOOTUTIL_CRYPTO_H_
#define __BOOTUTIL_CRYPTO_H_

#include "mcuboot_config/mcuboot_config.h"

#if (defined(MCUBOOT_USE_MBED_TLS) + \
     defined(MCUBOOT_USE_TINYCRYPT) + \
     defined(MCUBOOT_USE_NRF_EXTERNAL_CRYPTO) + \
     defined(MCUBOOT_USE_CC310)) != 1
    #error "One crypto backend must be defined either CC310, MBED_TLS or TINYCRYPT"
#endif

#ifdef MCUBOOT_USE_MBED_TLS
    #include <mbedtls/sha256.h>
#endif /* MCUBOOT_USE_MBED_TLS */

#ifdef MCUBOOT_USE_TINYCRYPT
    #include <tinycrypt/sha256.h>
#endif /* MCUBOOT_USE_TINYCRYPT */

#ifdef MCUBOOT_USE_CC310
    #include <cc310_glue.h>
#endif /* MCUBOOT_USE_CC310 */

#ifdef MCUBOOT_USE_NRF_EXTERNAL_CRYPTO
    #include <bl_crypto.h>
#endif /* MCUBOOT_USE_NRF_EXTERNAL_CRYPTO */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MCUBOOT_USE_MBED_TLS
typedef mbedtls_sha256_context bootutil_sha256_context;

static inline void bootutil_sha256_init(bootutil_sha256_context *ctx)
{
    mbedtls_sha256_init(ctx);
    (void)mbedtls_sha256_starts_ret(ctx, 0);
}

static inline void bootutil_sha256_update(bootutil_sha256_context *ctx,
                                          const void *data,
                                          uint32_t data_len)
{
    (void)mbedtls_sha256_update_ret(ctx, data, data_len);
}

static inline void bootutil_sha256_finish(bootutil_sha256_context *ctx,
                                          uint8_t *output)
{
    (void)mbedtls_sha256_finish_ret(ctx, output);
}
#endif /* MCUBOOT_USE_MBED_TLS */

#ifdef MCUBOOT_USE_TINYCRYPT
typedef struct tc_sha256_state_struct bootutil_sha256_context;
static inline void bootutil_sha256_init(bootutil_sha256_context *ctx)
{
    tc_sha256_init(ctx);
}

static inline void bootutil_sha256_update(bootutil_sha256_context *ctx,
                                          const void *data,
                                          uint32_t data_len)
{
    tc_sha256_update(ctx, data, data_len);
}

static inline void bootutil_sha256_finish(bootutil_sha256_context *ctx,
                                          uint8_t *output)
{
    tc_sha256_final(output, ctx);
}
#endif /* MCUBOOT_USE_TINYCRYPT */

#ifdef MCUBOOT_USE_CC310
static inline void bootutil_sha256_init(bootutil_sha256_context *ctx)
{
    cc310_sha256_init(ctx);
}

static inline void bootutil_sha256_update(bootutil_sha256_context *ctx,
                                          const void *data,
                                          uint32_t data_len)
{
    cc310_sha256_update(ctx, data, data_len);
}

static inline void bootutil_sha256_finish(bootutil_sha256_context *ctx,
                                          uint8_t *output)
{
    cc310_sha256_finalize(ctx, output);
}
#endif /* MCUBOOT_USE_CC310 */

#ifdef MCUBOOT_USE_NRF_EXTERNAL_CRYPTO
typedef bl_sha256_ctx_t bootutil_sha256_context;

static inline void bootutil_sha256_init(bootutil_sha256_context *ctx)
{
    bl_sha256_init(ctx);
}

static inline void bootutil_sha256_update(bootutil_sha256_context *ctx,
                                          const void * data,
                                          uint32_t data_len)
{
    bl_sha256_update(ctx, data, data_len);

}

static inline void bootutil_sha256_finish(bootutil_sha256_context *ctx,
                                          uint8_t * output)
{
    bl_sha256_finalize(ctx, output);
}
#endif /* MCUBOOT_USE_NRF_EXTERNAL_CRYPTO */

#ifdef __cplusplus
}
#endif

#endif /* __BOOTUTIL_SIGN_KEY_H_ */
