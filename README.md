This repository provides a thread-safe wrapper for the standard std::queue in C++. The QueueThreadSafe template class ensures safe access and manipulation of the queue in multi-threaded environments by utilizing mutexes to prevent data races and ensure thread synchronization.

Features

    Thread-Safe Access: Provides synchronized access to the queue's front, back, push, and pop operations.
    Standard Interface: Implements familiar methods from std::queue for easy integration.
    Customizable Container: Supports custom underlying containers through template parameters.

Requirements

    C++11 or later.

Usage

Ideal for use in multi-threaded applications where shared queue operations must be synchronized to avoid race conditions.
