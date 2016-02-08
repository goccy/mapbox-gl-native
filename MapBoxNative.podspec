Pod::Spec.new do |s|

  mapbox_root    = "$(PODS_ROOT)/../mapbox-gl-native"
  s.name         = "MapBoxNative"
  s.version      = "0.0.1"
  s.summary      = ""
  s.description  = ""
  s.homepage     = ""
  s.license      = { :type => 'MIT' }
  s.author       = { "goccy" => "goccy54@gmail.com" }
  s.public_header_files = 'include/mgbl/**/*.h'
  mason_packages     = "#{mapbox_root}/mason_packages"
  variant            = "#{mason_packages}/headers/variant/1.0/include"
  rapidjson          = "#{mason_packages}/headers/rapidjson/1.0.2/include"
  boost              = "#{mason_packages}/headers/boost/1.59.0/include"
  geojsonvt          = "#{mason_packages}/ios-9.2/geojsonvt/3.1.0/include"
  libuv              = "#{mason_packages}/ios-9.2/libuv/1.7.5/include"

  libuv_search_path     = "#{mason_packages}/ios-9.2/libuv/1.7.5/lib"
  geojsonvt_search_path = "#{mason_packages}/ios-9.2/geojsonvt/3.1.0/lib"
  ios_library_search_path = "#{libuv_search_path} #{geojsonvt_search_path}"
  s.ios.preserve_paths    = "#{libuv_search_path}/libuv.a #{geojsonvt_search_path}/libgeojsonvt.a"
  header_search_path = "#{mapbox_root} #{mapbox_root}/include #{mapbox_root}/src #{variant} #{rapidjson} #{boost} #{geojsonvt} #{libuv}"
  
  s.xcconfig = {
    HEADER_SEARCH_PATHS: header_search_path,
    LIBRARY_SEARCH_PATHS: ios_library_search_path
  }

  s.source        = { :git => "git@github.com:mapbox/mapbox-gl-native.git", :tag => "0.0.1" }
  s.source_files  = '*.{h,c,cpp}'
  s.requires_arc  = true
  s.ios.frameworks = 'GLKit', 'ImageIO', 'MobileCoreServices', 'QuartzCore', 'SystemConfiguration'
  s.ios.libraries  = 'c++', 'z', 'sqlite3', 'uv', 'geojsonvt'
  s.dependency 'cocos2dx'
  
  default_sources = [
    'asset_file_source', 'async_task', 'default_file_source', 'online_file_source', 'run_loop',
    'sqlite3', 'sqlite_cache', 'timer'
  ].map { |src| "platform/default/#{src}.{hpp,cpp}" }
  
  s.subspec 'source' do |ss|
    ss.source_files  = [ "*.{hpp,cpp}", "include/mbgl/{annotation,darwin,ios,map,platform,shader,sprite,storage,style,util}/**/*.{h,hpp}", "src/**/*.{hpp,cpp,c}", "platform/darwin/*.{h,mm,m}", "platform/ios/**/*.{h,m,mm}", default_sources ].flatten
    ss.exclude_files = "platform/darwin/settings_nsuserdefaults.mm"
  end
  
end
