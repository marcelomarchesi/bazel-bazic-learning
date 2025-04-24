// This file is just used as an example to link Rust code with C++ code.
// In this case C++ code is calling the function below.
// To be able to link it with C++ object code, the crate_type needed to be
// set here as this option still isn't supported in Bazel rust_rules.
#![crate_type = "cdylib"]
#[unsafe(no_mangle)]
pub extern "C" fn print_message(message: *const std::os::raw::c_char) {
    let c_str = unsafe {
        assert!(!message.is_null());
        std::ffi::CStr::from_ptr(message)
    };
    let message_str = c_str.to_str().expect("Invalid UTF-8 string");
    println!("Message from Rust: {}", message_str);
}