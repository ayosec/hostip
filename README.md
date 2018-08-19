# hostip

Show the IP address assigned to the interface assigned to the default gateway.

Only works on Linux.

## Installation

Build with `make`, and copy the `hostip` binary to a directory in your `$PATH`.

```bash
$ make
$ sudo install -o root hostip /usr/local/bin/
```

## Usage

Just type `host`

```bash
$ hostip 
10.0.0.17
```
