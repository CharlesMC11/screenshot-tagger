_sst_notify() {
  integer -r code=$1
  if (( code == 0 )); then
    subtitle='📷 Success'
    sound=Glass
  else
    subtitle="⚠️ Failure: $code"
    sound=Basso
  fi

  readonly msg="${${(f)mapfile[$LOG_FILE]}[-1]}"
  "$OSASCRIPT" -e "display notification \"${msg##*\]?}\" with title \"${SERVICE_NAME}\" subtitle \"${subtitle}\" sound name \"${sound}\""
}
