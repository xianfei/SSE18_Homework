# Code for chapter 04 - Debugging with the Scientific Method
# WITH BUGS!
# This code contains a single defect
# that is hard to find by looking at the symptoms or the code.
#
# The program should print codes of pressed keys.

from pygame.locals import KEYDOWN
import pygame


def event_loop(handle_key, delay=10):
    """"Processes events and updates callbacks."""
    while True:
        pygame.event.pump()
        event = pygame.event.poll()
        if event.type == KEYDOWN:
            handle_key(event.key)
        pygame.time.delay(delay)


if __name__ == '__main__':
    pygame.init()
    event_loop(print)
