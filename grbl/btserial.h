/* 
 * File:   btserial.h
 * Author: M91541
 *
 * Created on August 19, 2019, 2:41 PM
 */

#ifndef BTSERIAL_H
#define	BTSERIAL_H

#ifdef	__cplusplus
extern "C" {
#endif

    void bluetooth_serial_init(void);
    void bluetooth_serial_write(uint8_t data);
    
#ifdef	__cplusplus
}
#endif

#endif	/* BTSERIAL_H */

