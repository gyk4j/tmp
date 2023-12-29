divert(-1)
dnl
dnl By using this file, you agree to the terms and conditions set
dnl forth in the LICENSE file which can be found at the top level of
dnl the sendmail distribution (sendmail-8.12).
dnl
dnl     Contributed by Andrzej Filip and Dilyan Palauzov
LOCAL_CONFIG
# cyrus - map for checking cyrus mailbox presence
Kcyrus socket -T<TMPF> -a<OK> local:/var/imap/socket/smmapd

LOCAL_RULESETS
SLocal_localaddr
R$+     $: $1 $| $(cyrus $1 $: $)
R$+ $|                $#error $@ 5.1.1 $: "550 User unknown."
R$+ $| $*<TMPF>       $#error $@ 4.3.0 $: "451 Temporary system failure. Please try again later."
R$+ $| $*<OK>         $#cyrusv2 $@ $: $1
R$+ $| $*             $: $1

