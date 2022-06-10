| Proposal ID      |                                                                                  |
| ---------------- | -------------------------------------------------------------------------------- |
| Name             | SYCL Improved host task interoperability                                         |
| Date of Creation | 7 June 2022                                                                      |
| Target           | SYCL Next                                                                        |
| Current Status   | _Draft_                                                                          |
| Reply-to         | Nicolas Miller <nicolas.miller@codeplay.com>                                     |
| Original author  | Nicolas Miller <nicolas.miller@codeplay.com>                                     |
| Contributors     | Tadej Ciglaric <tadej.ciglaric@codeplay.com>, Gordon Brown <gordon@codeplay.com> |

# Improved host task

In the SYCL 2020 specification the SYCL `host_task` allows for host work to be
scheduled within the SYCL DAG, in addition it can also be used to perform
interoperability work.

However the interoperability provided in the `host_task` doesn't include any
`sycl::event` interoperability, or any way to model native dependencies between
SYCL submitted work and work submitted with interoperability.

This means that synchronization between SYCL DAG tasks and interoperability
tasks enqueued using the `host_task` have to be done on host, even if the device
and SYCL implementation would support handling these dependencies on the device.
Which makes the SYCL 2020 `host_task` interface for interoperability inefficient
on some platforms.

This proposal aims to address these issues, and improve on the SYCL 2020
`host_task`, to provide better integrated interoperability solutions.

