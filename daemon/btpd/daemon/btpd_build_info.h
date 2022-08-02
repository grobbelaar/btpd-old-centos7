struct btpd_build_info{
  bool enabled() const;
  const char* name() const;
  const char* version_tag() const;
  const char* version_ex() const;
  const char* compiler_version() const;
  const char* build_type() const;
  const char* build_date() const;
  const char* build_flags() const;
  const char* build_count() const;
  const char* branch() const;
  const char* commit() const;
  const char* commit_date() const;
  const char* commit_author() const;
  const char* commit_message() const;
  const char* initial_author() const;
  const char* all_authors() const;
};
