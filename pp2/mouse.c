#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>




int hook_id=0;

int mouse_subscribe_int(uint8_t *bit_no)
{
    *bit_no = (uint8_t) hook_id;

    if (sys_irqsetpolicy(12,IRQ_REENABLE|IRQ_EXCLUSIVE,&hook_id)!=0) return 1;
    return 0;
}

int mouse_unsubscribe_int()
{
    if (sys_irqrmpolicy(&hook_id)!=0) return 1;
    return 0;
}

int util_sys_inb(uint32_t port, uint8_t *value)
{
    uint32_t temp=(uint32_t) (value);

    if (sys_inb(port,&temp)!=0) return 1;

    *value=temp;

    return 0;
}

uint8_t bytes[4],size=0;

int timer_ih()
{
    for (int i=0;i<4;i++)
    {
        uint8_t current_byte;
        if (util_sys_inb(0x60,&current_byte)!=0) return 1;
        bytes[i]=current_byte;
    }
    return 0;
}

void process_packet(struct pp_packet pp)
{
    pp->bytes[0]=bytes[0];
    pp->bytes[1]=bytes[1];
    pp->bytes[2]=bytes[2];
    pp->bytes[3]=bytes[3];
    pp->lb=((bytes[0]&BIT(6))>>6);
    pp->mb=((bytes[0]&BIT(5))>>5);
    pp->rb=((bytes[0]&BIT(4))>>4);
    pp->delta_x=bytes[2];
    pp->delta_y=bytes[3];
    pp->delta_z=bytes[1];
    pp->x_ov=((bytes[0]&BIT(2))>>2);
    pp->x_ov=((bytes[0]&BIT(3))>>3);
}



int pp_test_packet(uint32_t cnt)
{
  int ipc_status,r;
  message msg;
  uint8_t bit_no,control,initial_control;
  uint32_t irq_set = 0;
  
  if (util_sys_inb(0x64,&initial_control)!=0)return 1;
  control=initial_control;
  control|=BIT(7);
  control|=BIT(3);
  control|=BIT(0);

  if (sys_outb(0x64,control)!=0) return 1;

  if (mouse_subscribe_int(&bit_no)!=0) return 1;

  struct pp_packet pp;

  uint32_t count=0;
  irq_set = (uint32_t)(BIT(bit_no));

 
 
  while( count<cnt ) { /* You may want to use a different condition */
     /* Get a request message. */
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                    count++;
                    if (timer_ih()!=0) return 1;
                    process_packet(&pp);
                    pp_display_packet(&pp);
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
 }
if (mouse_unsubscribe_int()!=0) return 1;
if (sys_outb(0x64,initial_control)!=0) return 1;

 return 0;
}
