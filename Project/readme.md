## Problem:

Internet protocol doesn't guarentee packet delivery,in-order delivery and the integrity of the data in packtes. 
Bits in the packet can get corrupted (flipped from 0->1 and vice-versa). While using socket programming for TCP, 
it might happen that the intended message may get changed in the channel and the receiver receives a wrong message.
The sender may also get an erroneous acknowledgement **(ACK & NACK)** for which the sender may send duplicate data or 
the next data before the actual acknowledgement.

## Solution: 

The objective of Reliable Data Transfer is to ensure that the data stream is uncorrupted, without gaps, without 
duplication and in sequence. That is, the byte stream is exactly the same bytestream that was sent by the end 
system on the other side of connection. We have used the concept of **CRC(Cyclic Redundancy Check)** which is one
the most widely used error detection techniques in today's computer networks. The steps of CRC is given below.

For an N bit CRC:
* Append  N no of zeros to the message.
* Divide the new message by the (N+1) bit polynomial.
* Perform Modulo-2 arithmetic(XOR).
* Get the remainder polynomial.
* Append  the remainder to the message and send the encoded message(msg_length+N bits) to the other end.
* Retrieve the encoded message.
* Divide the encoded message by the same remainder poly (CRC) to check whether the message received is correct.

While adding errors to data, we could see that the corrupted data was being received by the server. So, we have
tried to retransmit the correct data again and again unless and until the server receives it in proper form. 
The client will also wait for the positive ackwoledgement(ACK) before sending more data. 

## Implementation:

* Generation of CRC table for faster lookup.
* Connection setup using **TCP SOCKETS**.
* Modulo 2 CRC computation.
* Connection from Client and introduction of error in the message incorporating **BER(Bit Error Rate)**.
* Introduction of error in ACK and NACK using similar technique – **“Random flip”**.
* Checking for correct message at server and sending ACK for correct message, NACK for wrong message.
* If acknowledgement is not received within 5 secs, **TIMEOUT** occurs and the data needs to be retransmitted.

## Gaps in implementation:

* We could not create a timeout scenario even though we have added it in the client program.
* We have not added the functionality of two way communication.
* We could not exactly get a fair idea of how long does it take for the correct message to get transmitted
  till the acknowledgement is recieved.

## Challenges:

* We are getting a random nature of timing for a set of probabilities of error.
* As we are inserting error into both data and acknowledgements , we could not figure out 
  whether the receiver has received the NACK because of error in NACK/ACK or because of error in data.
  
## Concepts for Reference:


