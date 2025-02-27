LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := clogger
LOCAL_SRC_FILES := \
	snlogger_jni.c \
	clogger_android_string.c \
	clogger_print.c \
	clogger_platform.c \
	../../../lib/src/clogger_message_queue.c \
	../../../lib/src/clogger.c \
	../../../lib/src/clogger_list.c \
	../../../lib/src/clogger_lock.c \
	../../../lib/src/clogger_logan.c \
	../../../lib/src/clogger_savefile.c \
	../../../lib/src/clogger_utils.c \
	../../../lib/src/clogger_ref.c \
	../../../lib/3rd/Clogan/aes_util.c \
	../../../lib/3rd/Clogan/base_util.c \
	../../../lib/3rd/Clogan/cJSON.c \
	../../../lib/3rd/Clogan/clogan_core.c \
	../../../lib/3rd/Clogan/console_util.c \
	../../../lib/3rd/Clogan/construct_data.c \
	../../../lib/3rd/Clogan/directory_util.c \
	../../../lib/3rd/Clogan/json_util.c \
	../../../lib/3rd/Clogan/mmap_util.c \
	../../../lib/3rd/Clogan/zlib_util.c \
	../../../lib/3rd/mbedtls/library/aes.c \
	../../../lib/3rd/mbedtls/library/aesni.c \
	../../../lib/3rd/mbedtls/library/arc4.c \
	../../../lib/3rd/mbedtls/library/asn1parse.c \
	../../../lib/3rd/mbedtls/library/asn1write.c \
	../../../lib/3rd/mbedtls/library/base64.c \
	../../../lib/3rd/mbedtls/library/bignum.c \
	../../../lib/3rd/mbedtls/library/blowfish.c \
	../../../lib/3rd/mbedtls/library/camellia.c \
	../../../lib/3rd/mbedtls/library/ccm.c \
	../../../lib/3rd/mbedtls/library/certs.c \
	../../../lib/3rd/mbedtls/library/cipher.c \
	../../../lib/3rd/mbedtls/library/cipher_wrap.c \
	../../../lib/3rd/mbedtls/library/cmac.c \
	../../../lib/3rd/mbedtls/library/ctr_drbg.c \
	../../../lib/3rd/mbedtls/library/debug.c \
	../../../lib/3rd/mbedtls/library/des.c \
	../../../lib/3rd/mbedtls/library/dhm.c \
	../../../lib/3rd/mbedtls/library/ecdh.c \
	../../../lib/3rd/mbedtls/library/ecdsa.c \
	../../../lib/3rd/mbedtls/library/ecjpake.c \
	../../../lib/3rd/mbedtls/library/ecp.c \
	../../../lib/3rd/mbedtls/library/ecp_curves.c \
	../../../lib/3rd/mbedtls/library/entropy.c \
	../../../lib/3rd/mbedtls/library/entropy_poll.c \
	../../../lib/3rd/mbedtls/library/error.c \
	../../../lib/3rd/mbedtls/library/gcm.c \
	../../../lib/3rd/mbedtls/library/havege.c \
	../../../lib/3rd/mbedtls/library/hmac_drbg.c \
	../../../lib/3rd/mbedtls/library/md.c \
	../../../lib/3rd/mbedtls/library/md2.c \
	../../../lib/3rd/mbedtls/library/md4.c \
	../../../lib/3rd/mbedtls/library/md5.c \
	../../../lib/3rd/mbedtls/library/md_wrap.c \
	../../../lib/3rd/mbedtls/library/memory_buffer_alloc.c \
	../../../lib/3rd/mbedtls/library/net_sockets.c \
	../../../lib/3rd/mbedtls/library/oid.c \
	../../../lib/3rd/mbedtls/library/padlock.c \
	../../../lib/3rd/mbedtls/library/pem.c \
	../../../lib/3rd/mbedtls/library/pk.c \
	../../../lib/3rd/mbedtls/library/pk_wrap.c \
	../../../lib/3rd/mbedtls/library/pkcs11.c \
	../../../lib/3rd/mbedtls/library/pkcs12.c \
	../../../lib/3rd/mbedtls/library/pkcs5.c \
	../../../lib/3rd/mbedtls/library/pkparse.c \
	../../../lib/3rd/mbedtls/library/pkwrite.c \
	../../../lib/3rd/mbedtls/library/platform.c \
	../../../lib/3rd/mbedtls/library/ripemd160.c \
	../../../lib/3rd/mbedtls/library/rsa.c \
	../../../lib/3rd/mbedtls/library/sha1.c \
	../../../lib/3rd/mbedtls/library/sha256.c \
	../../../lib/3rd/mbedtls/library/sha512.c \
	../../../lib/3rd/mbedtls/library/ssl_cache.c \
	../../../lib/3rd/mbedtls/library/ssl_ciphersuites.c \
	../../../lib/3rd/mbedtls/library/ssl_cli.c \
	../../../lib/3rd/mbedtls/library/ssl_cookie.c \
	../../../lib/3rd/mbedtls/library/ssl_srv.c \
	../../../lib/3rd/mbedtls/library/ssl_ticket.c \
	../../../lib/3rd/mbedtls/library/ssl_tls.c \
	../../../lib/3rd/mbedtls/library/threading.c \
	../../../lib/3rd/mbedtls/library/timing.c \
	../../../lib/3rd/mbedtls/library/version.c \
	../../../lib/3rd/mbedtls/library/version_features.c \
	../../../lib/3rd/mbedtls/library/x509.c \
	../../../lib/3rd/mbedtls/library/x509_create.c \
	../../../lib/3rd/mbedtls/library/x509_crl.c \
	../../../lib/3rd/mbedtls/library/x509_crt.c \
	../../../lib/3rd/mbedtls/library/x509_csr.c \
	../../../lib/3rd/mbedtls/library/x509write_crt.c \
	../../../lib/3rd/mbedtls/library/x509write_csr.c \
	../../../lib/3rd/mbedtls/library/xtea.c \

LOCAL_C_INCLUDES += \
	../../../lib/include \
	../../../lib/3rd/Clogan \
	../../../lib/3rd/mbedtls/include 
	
LOCAL_CFLAGS += -std=c99 -DANDROID -DDEBUG
LOCAL_LDLIBS += -llog -lz

include $(BUILD_SHARED_LIBRARY)